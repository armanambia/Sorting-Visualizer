#include "menu.h"

// initializes the UI with the menu buttons
UI::UI(sf::RenderWindow* win, sf::Font* font) : _win(win), _font(font)
{
	this->_nav.setFillColor(sf::Color(211, 211, 211, 255));
	this->_nav.setSize(sf::Vector2f(200, 800));
	this->_font = font;
	initButtons();
}

// deletes all the buttons in the buttons vector
UI::~UI()
{
	auto itr = this->buttons.begin();
	for (itr = this->buttons.begin(); itr != buttons.end(); ++itr) {
		delete itr->second;
	}
}

// processes the mouse click to get the button
int UI::processMouse(sf::Vector2f mousePos)
{
	for (auto& it : this->buttons) {
		it.second->update(mousePos);
	}
	if (this->buttons["Bubble Sort"]->isPressed()) {
		return 1;
	}
	else if (this->buttons["Selection Sort"]->isPressed()) {
		return 2;
	}
	else if (this->buttons["Insertion Sort"]->isPressed()) {
		return 3;
	}
	else if (this->buttons["Merge Sort"]->isPressed()) {
		return 4;
	}
	else if (this->buttons["Reset"]->isPressed()) {
		return 0;
	}
	return -1;
}

// initialize buttons 
void UI::initButtons()
{
	this->buttons["Bubble Sort"] = new Button(20, 100, 160, 60, _font, "Bubble Sort",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["Selection Sort"] = new Button(20, 200, 160, 60, _font, "Selection Sort",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["Insertion Sort"] = new Button(20, 300, 160, 60, _font, "Insertion Sort",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["Merge Sort"] = new Button(20, 400, 160, 60, _font, "Merge Sort",
		sf::Color(70, 70, 70, 200), sf::Color(1150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["Reset"] = new Button(20, 600, 160, 60, _font, "Reset",
		sf::Color(37, 156, 31, 200), sf::Color(88, 250, 80, 255), sf::Color(35, 219, 26, 200));
}

// draws the buttons onto the screen
void UI::renderButtons()
{
	for (auto& it : this->buttons) {
		it.second->render(_win);
	}
}

// draws the window and the button
void UI::render()
{
	this->_win->draw(this->_nav);
	renderButtons();
}

// clears all the bars on the screen
void SortHandler::clearElements()
{
	auto itr = this->_bars.begin();
	for (itr = this->_bars.begin(); itr != _bars.end(); ++itr) {
		delete* itr;
	}
	_bars.clear();
}

// Sort Handler creates the UI and creates the sorting interface
SortHandler::SortHandler(sf::RenderWindow* win, sf::Font* font) : UI(win, font)
{
	this->_sortArea.setFillColor(sf::Color::Black);
	this->_sortArea.setPosition(sf::Vector2f(200, 0));
	this->_sortArea.setSize(sf::Vector2f(1000, 800));
	_isSorting = false;
	setText();
	reset();
}

// SortHandler deletes all the elements
SortHandler::~SortHandler()
{
	clearElements();
}

// sets the text of the tooltip
void SortHandler::setText()
{
	this->_tipText.setFillColor(sf::Color::White);
	this->_tipText.setFont(*_font);
	std::string tip = "";
	if (!_sorted) {
		tip += "Press Right Arrow (->) to Speed Up | Left Arrow (<-) to Slow Down | Escape to Stop Sort";
		tip += "\tCurrent Speed: " + std::to_string(10 - (_speed - 1) / 50);
	}
	else {
		tip += "Please Reset Screen to Sort Again";
	}
	
	this->_tipText.setString(tip);
	this->_tipText.setCharacterSize(20);
	this->_tipText.setPosition(
		_sortArea.getPosition().x + 100 + (this->_sortArea.getGlobalBounds().width / 2.f) - this->_tipText.getGlobalBounds().width / 2.f,
		50.0f
	);
}

// resets the bars on the screen with different values, also resets buttons
void SortHandler::reset()
{
	srand(time(0));
	_sorted = false;
	_speed = 101;
	_time = sf::milliseconds(_speed);
	_bars.clear();
	float x_start = 260;
	// accounts for width of 30 + 14.2105 of free space
	float gap = 44.2105;
	float x_pos;
	int val;
	for (int i = 0; i < 25; i++) {
		x_pos = x_start + float(i * gap);
		val = rand() % 550 + 100;
		_bars.push_back(new Bar(x_pos, val, sf::Color::Blue, _font));
	}
	detectInput();
}

// resets the colors back to blue
void SortHandler::resetColors()
{
	for (int i = 0; i < 25; i++) {
		_bars[i]->setColor(sf::Color::Blue);
	}
}

// detects input of the keys pressed
void SortHandler::detectInput()
{
	sf::Event event;
	while (_win->pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed:
			_win->close();
			break;
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::Right) {
				if (_speed > 1) {
					_speed -= 50;
					_time = sf::milliseconds(_speed);
				}
			}
			else if (event.key.code == sf::Keyboard::Left) {
				if (_speed < 451) {
					_speed += 50;
					_time = sf::milliseconds(_speed);
				}
			}
			else if (event.key.code == sf::Keyboard::Escape) {
				setSorting(false);
			}
		}
	}
}

// calls the process mouse from UI and calls the corresponding to the sort
void SortHandler::processMouse(sf::Vector2f mousePos)
{
	int val = UI::processMouse(mousePos);
	if (val != -1) {
		if (val == 0) {
			reset();
		}
		else if (val == 1) {
			bubbleSort();
		}
		else if (val == 2) {
			selectionSort();
		}
		else if (val == 3) {
			insertionSort();
		}
		else if (val == 4) {
			mergeSort();
		}
	}
}

// implements bubble sort
void SortHandler::bubbleSort()
{
	if(!_sorted){
	int n = 25;
	int i, j;
	setSorting(true);
	for (i = 0; i < n - 1 && _isSorting == true; i++)
	{
		for (j = 0; j < n - i - 1 && _isSorting == true; j++)
			if (_bars[j]->val() > _bars[j + 1]->val())
			{
				sf::sleep(_time);
				_bars[j]->setColor(sf::Color::Red);
				_bars[j + 1]->setColor(sf::Color::Red);
				render();
				_bars[j]->swap(_bars[j + 1]);
				sf::sleep(_time);
				render();
				_bars[j]->setColor(sf::Color::Blue);
				_bars[j + 1]->setColor(sf::Color::Blue);
				sf::sleep(_time);
			}
	}
	setSorting(false);
	resetColors();
	setSorted();	
	}
}

// implements selection sort
void SortHandler::selectionSort()
{
	if(!_sorted){
	int i, j, min;
	int n = _bars.size();
	setSorting(true);
	for (i = 0; i < n - 1 && _isSorting; i++)
	{
		min = i;
		_bars[min]->setColor(sf::Color::Green);
		sf::sleep(_time);
		render();
		for (j = i + 1; j < n && _isSorting; j++)
		{
			_bars[j]->setColor(sf::Color::Yellow);
			sf::sleep(_time);
			render();
			if (_bars[j]->val() < _bars[min]->val())
			{
				_bars[min]->setColor(sf::Color::Blue);
				_bars[j]->setColor(sf::Color::Green);
				min = j;
			}
			else {
				_bars[j]->setColor(sf::Color::Blue);
			}			
			sf::sleep(_time);
			render();			
		}
		_bars[min]->swap(_bars[i]);		
		_bars[i]->setColor(sf::Color::Red);
		if( i != min)
			_bars[min]->setColor(sf::Color::Blue);
		sf::sleep(_time);
		render();
	}
	if(_isSorting){
		_bars[n - 1]->setColor(sf::Color::Red);
		sf::sleep(_time);
		render();
	}
	resetColors();
	setSorting(false);
	setSorted();
	}
}

// implements insertion sort
void SortHandler::insertionSort()
{
	if (!_sorted ){
	setSorting(true);
	int n = _bars.size();
	int i, key, j;
	for (i = 1; i < n && _isSorting; i++)
	{
		key = _bars[i]->val();
		j = i - 1;
		_bars[j + 1]->setColor(sf::Color::Red);
		_bars[j]->setColor(sf::Color::Green);
		sf::sleep(_time);
		render();
		while (j >= 0 && _bars[j]->val() > key && _isSorting)
		{
			_bars[j + 1]->setColor(sf::Color::Red);
			_bars[j]->setColor(sf::Color::Green);
			sf::sleep(_time);
			render();
			_bars[j + 1]->swap(_bars[j]);
			_bars[j + 1]->setColor(sf::Color::Yellow);
			_bars[j]->setColor(sf::Color::Red);
			sf::sleep(_time);
			render();
			j = j - 1;
		}
		if(j >=0)
			_bars[j]->setColor(sf::Color::Yellow);
		sf::sleep(_time);
		render();
		_bars[j + 1]->setVal(key);
		_bars[j + 1]->setColor(sf::Color::Yellow);
		sf::sleep(_time);
		render();
	}
	resetColors();
	setSorting(false);
	setSorted();
	}
}

// merges the sub vectors of barsVect together together in a sorted form
void SortHandler::merge(std::vector<Bar>& barsVect, int l, int m, int r, sf::Color &color)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	/* create temp arrays */
	std::vector<Bar> L;
	std::vector<Bar> R;
	for (i = 0; i < n1; i++)
		L.push_back( barsVect[l + i]);
	for (j = 0; j < n2; j++)
		R.push_back( barsVect[m + 1 + j]);
	i = 0;
	j = 0; 
	k = l; 
	while (i < n1 && j < n2) {
		if (L[i].val() <= R[j].val()) {
			barsVect[k] = L[i];
			i++;
		}
		else {
			barsVect[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		barsVect[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		barsVect[k] = R[j];
		j++;
		k++;
	}	
	for (int i = l; i <= r && _isSorting; i++) {
		(*_bars[i]) = barsVect[i];
		_bars[i]->setColor(color);
		sf::sleep(_time);
		render();
	}
}

// implementation of recursive merge sort
void SortHandler::mergeSortHelper(std::vector<Bar>& barsVect, int l, int r, sf::Color &color)
{
	if (l < r && _isSorting) {
		int m = l + (r - l) / 2;
		srand(time(0));
		sf::Color curColor = sf::Color(rand() * 255 + 1, rand() * 255 + 1, rand() * 255 + 1, 255);
		mergeSortHelper(barsVect, l, m, curColor);
		mergeSortHelper(barsVect, m + 1, r, curColor);
		merge(barsVect, l, m, r, curColor);
	}
}

// calls merge sort
void SortHandler::mergeSort()
{
	if (!_sorted){
		setSorting(true);
		std::vector<Bar> copyBars;
		for (auto element : _bars) {
			copyBars.push_back(*element);
		}
		srand(time(0));
		sf::Color curColor = sf::Color(rand() * 255 + 1, rand() * 255 + 1, rand() * 255 + 1, 255);
		mergeSortHelper(copyBars, 0, copyBars.size() - 1, curColor);
		copyBars.clear();
		resetColors();
		setSorting(false);
		setSorted();
	}	
}

// sets variable _sorted to true if _bars is sorted
// and _sorted to false if any of them are out of order
void SortHandler::setSorted()
{
	for (int i = 0; i < 24; i++) {
		if (_bars[i]->val() > _bars[i + 1]->val())
		{
			_sorted = false;
			return;
		}	
	}
	_sorted = true;
}

// draws the UI's buttons as well as sorting area with formatted bars to the screen
void SortHandler::render()
{
	_win->clear();
	UI::render();
	this->_win->draw(this->_sortArea);
	if(_isSorting || _sorted){
		setText();
		this->_win->draw(this->_tipText);
	}
	auto itr = this->_bars.begin();
	for (itr = this->_bars.begin(); itr != _bars.end(); ++itr) {
		(*itr)->render(_win);
	}
	detectInput();
	_win->display();
}

// sets _isSorting to a value which tracks if a sort is being performed currently 
void SortHandler::setSorting(bool val)
{
	_isSorting = val;
}

