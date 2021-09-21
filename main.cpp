#include"includes.h"
#include"room.h"
using namespace sf;




RenderWindow window(VideoMode(720, 680), "Simulation of ventilation");

Text text;
Font font; 
int** Plot;



void EventHandle(Event& event) 
{
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
		}
	}
}

void GridDraw(int x_offset, int y_offset)
{

	std::string s;

	text.setPosition(sf::Vector2f(x_offset - 10, y_offset + P_HEIGHT));
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::Black);
	text.setString("0");
	window.draw(text);



	sf::RectangleShape hLine(sf::Vector2f(1, P_HEIGHT));
	hLine.setRotation(180);
	hLine.setFillColor(sf::Color::Color(180,180,180));
	sf::RectangleShape vLine(sf::Vector2f(P_WIDTH, 1));
	vLine.setFillColor(sf::Color::Color(180, 180, 180));
	for (int i = 0; i < P_WIDTH/50; i++)
	{

		s = std::to_string((i * 2.5));

		s.replace(4, 6, "");
		text.setString(s);
		hLine.setPosition(sf::Vector2f(x_offset + 50 * i, y_offset - 1 + P_HEIGHT ));
		
		
		if(i!=0)text.setPosition(sf::Vector2f(x_offset-5 + 50 * i, y_offset - 1 + P_HEIGHT));

		window.draw(text);
		window.draw(hLine);
	}

	for (int i = 0; i < P_HEIGHT / 50; i++)
	{
		s = std::to_string((i * 0.5));

		s.replace(3,6,"");
		text.setString(s);
		vLine.setPosition(sf::Vector2f(x_offset + 1, y_offset + P_HEIGHT - 50 * i));
		if (i != 0) {
			text.setPosition(sf::Vector2f(x_offset - 35, y_offset + P_HEIGHT -12 - 50 * i));
			window.draw(text);
		}
		window.draw(vLine);
	}


	text.setString("y,  %");

	text.setPosition(sf::Vector2f(x_offset - 20, y_offset - 25));

	window.draw(text);


	text.setString("t, min");

	text.setPosition(sf::Vector2f(x_offset +P_WIDTH, y_offset +P_HEIGHT+10));

	window.draw(text);

	sf::RectangleShape yAxis(sf::Vector2f(3, P_HEIGHT));
	yAxis.setFillColor(sf::Color::Black);
	sf::RectangleShape xAxis(sf::Vector2f(P_WIDTH,3));
	xAxis.setFillColor(sf::Color::Black);




	sf::CircleShape arrow;
	arrow.setRadius(6.5f);
	arrow.setPointCount(3);
	arrow.setPosition(sf::Vector2f(x_offset-6.5 , y_offset-3));
	arrow.setFillColor(sf::Color::Blue);


	yAxis.setRotation(180);

	yAxis.setPosition(sf::Vector2f(x_offset+1, y_offset+P_HEIGHT));
	xAxis.setPosition(sf::Vector2f(x_offset, y_offset-1 + P_HEIGHT));
	
	window.draw(xAxis);
	window.draw(yAxis);


	window.draw(arrow);


	arrow.setRotation(90);
	arrow.setPosition(sf::Vector2f(x_offset + 7 + P_WIDTH, y_offset - 5.5 + P_HEIGHT));
	arrow.setFillColor(sf::Color::Red);

	window.draw(arrow);

}

void PlotDrawHandler(Room& room,int x_offset, int y_offset)
{
	sf::RectangleShape pixel(sf::Vector2f(1, 1));
	pixel.setFillColor(sf::Color::Red);
	sf::RectangleShape plotBg(sf::Vector2f(P_HEIGHT,P_WIDTH));
	plotBg.setFillColor(sf::Color::White);
	plotBg.setPosition(sf::Vector2f(x_offset, y_offset));
	window.draw(plotBg);

	GridDraw(x_offset, y_offset);

	room.DrawPlot(Plot);
	for (int i = 0; i < P_HEIGHT; i++) {
		for (int j = 0; j < P_WIDTH; j++) {
			if (Plot[i][j] == 1) {
				pixel.setPosition(sf::Vector2f(x_offset + j, y_offset + i));
				window.draw(pixel);
			}
		}
	}
}



void WindowHandler(Event& event, Room& room)
{
	window.clear(Color::Color(200,200,200));

	PlotDrawHandler(room, 100,40);

	room.CalculatePlot();

	EventHandle(event);

	window.display();
}




int main(int argc, char* argv[])
{
	window.setFramerateLimit(15);
	Room room(220, 1.03, 10, 0.06, 0.04);

	font.loadFromFile("arial.ttf");

	text.setFont(font);

	if (argc > 5) 
	{
		room.SetNew(std::stof(argv[1]), std::stof(argv[2]), std::stof(argv[3]), std::stof(argv[4]), std::stof(argv[5]) );
	}
	Plot = new int* [P_HEIGHT];
	for (int i = 0; i < P_WIDTH; i++)
	{
		Plot[i] = new int[P_WIDTH];
	}


	if (argc >5 && std::strcmp(argv[6], "nogui")==0) 
	{
		double t = 0;
		for (int i = 0; i < P_WIDTH; i++)
		{

			t = (room.OutDependency((double)i / 20) );

			printf("%f :  %f\n", (double)i / 20, t);
		}
		
	}


	else {

		while (window.isOpen())
		{
			Event event;

			WindowHandler(event, room);
		}
	}
	for (int i = 0; i < P_WIDTH; i++)
	{
		delete[] Plot[i];
	}
	delete[] Plot;

}