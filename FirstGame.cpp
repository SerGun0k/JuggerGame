#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> 
#include <map.h> //подключили код с картой
#include <View.h> //подключили код с камерой
#include <sstream>
#include <chrono>

using namespace sf;



////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player {
private:
	float x, y;
public:
	float w, h, dx, dy, speed;
	int dir, playerScore, health;//новая переменная, хранящая очки игрока
	bool life, Game;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String F, float X, float Y, float W, float H) {
		dx = 0; dy = 0; speed = 0; dir = 0, playerScore = 0, health = 100;
		life = true;
		Game = true;
		File = F;
		w = W; h = H;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(255, 255, 255));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
	void update(float time)
	{
		switch (dir)
		{
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
		}

		x += dx * time;
		y += dy * time;

		speed = 0;
		interactionWithMap();//вызываем функцию, отвечающую за взаимодействие с картой

		if (health <= 0) { life = false; speed = 0; }//если жизней меньше либо равно 0, то умираем и исключаем движение игрока после смерти

		if (playerScore >= 10) { Game = false; speed = 0; }

		sprite.setPosition(x, y);
	}

	float getplayercoordinateX() {	//этим методом будем забирать координату Х	
		return x;
	}
	float getplayercoordinateY() {	//этим методом будем забирать координату Y 	
		return y;
	}

	void interactionWithMap()//ф-ция взаимодействия с картой
	{

		for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32
			for (int j = x / 32; j < (x + w) / 32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
			{
				if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
				{
					if (dy > 0)//если мы шли вниз,
					{
						y = i * 32 - h;//то строим координату у персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
					}
					if (dy < 0)
					{
						y = i * 32 + 32;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх 
					}
					if (dx > 0)
					{
						x = j * 32 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
					}
					if (dx < 0)
					{
						x = j * 32 + 32;//аналогично идем влево
					}
				}

				if (TileMap[i][j] == 's') { //если символ равен 's' (камень)
					playerScore++;//если взяли камень, переменная playerScore=playerScore+1;
					TileMap[i][j] = ' ';//убираем камень
				}
				if (TileMap[i][j] == 'f') {
					health -= 40;//если взяли ядовитейший в мире цветок,то переменная health=health-40;
					TileMap[i][j] = ' ';//убрали цветок
				}

				if (TileMap[i][j] == 'h') {
					health += 20;//если взяли сердечко,то переменная health=health+20;
					TileMap[i][j] = ' ';//убрали сердечко
				}
			}
	}

};



int main()
{

	sf::Font font;//шрифт 
	font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	sf::Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст.
	// Музыкальное сопровождение
	sf::SoundBuffer buffer1;
	buffer1.loadFromFile("Audio/Music_default_ui_startup_01.mp3.wav");
	sf::Sound sound1;
	sound1.setBuffer(buffer1);
	sound1.play();

	sf::SoundBuffer buffer3;
	buffer3.loadFromFile("Audio/Jug_death_09_ru.mp3.wav");
	sf::Sound sound3;
	sound3.setBuffer(buffer3);

	sf::SoundBuffer buffer2;
	buffer2.loadFromFile("Audio/Jug_bottle_03_ru.mp3.wav");
	sf::Sound sound2;
	sound2.setBuffer(buffer2);

	sf::SoundBuffer buffer4;
	buffer4.loadFromFile("Audio/Jug_win_03_ru.mp3.wav");
	sf::Sound sound4;
	sound4.setBuffer(buffer4);
	


	float a = 47, b = 63;
	RenderWindow window(sf::VideoMode(720, 560), "FirstGame");

	view.reset(sf::FloatRect(0, 0, 720, 560));//размер "вида" камеры при создании объекта вида камеры. (потом можем менять как хотим)

	Image map_image;//объект изображения для карты
	map_image.loadFromFile("Images/map.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

	Player p("Jugger.png", 250, 250, a, b);

	float CurrentFrame = 0;
	Clock clock;
	Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры 
	int gameTime = 0;//объявили игровое время, инициализировали.

	

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
		if ((p.life) && (p.Game))
		{
			if ((Keyboard::isKeyPressed(Keyboard::Left))) {
				p.dir = 1; p.speed = 0.1;
				CurrentFrame += 0.006 * time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				p.sprite.setTextureRect(IntRect(a * int(CurrentFrame), b, a, b));
				getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());//передаем координаты игрока в функцию управления камерой
			}

			else if ((Keyboard::isKeyPressed(Keyboard::Right))) {
				p.dir = 0; p.speed = 0.1;
				CurrentFrame += 0.006 * time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				p.sprite.setTextureRect(IntRect(a * int(CurrentFrame), 2 * b, a, b));
				getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());//передаем координаты игрока в функцию управления камерой
			}

			else if ((Keyboard::isKeyPressed(Keyboard::Up))) {
				p.dir = 3; p.speed = 0.1;
				CurrentFrame += 0.006 * time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				p.sprite.setTextureRect(IntRect(a * int(CurrentFrame), 3 * b, a, b));
				getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());//передаем координаты игрока в функцию управления камерой

			}

			else if ((Keyboard::isKeyPressed(Keyboard::Down))) {
				p.dir = 2; p.speed = 0.1;
				CurrentFrame += 0.006 * time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				p.sprite.setTextureRect(IntRect(a * int(CurrentFrame), 0, a, b));
				getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());//передаем координаты игрока в функцию управления камерой


			}
			getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}

		// BATTLECRY

		if ((Keyboard::isKeyPressed(Keyboard::F))) {
			sound2.play();
		}
		p.update(time);


		window.clear();

		/////////////////////////////Рисуем карту/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
				if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));//добавили цветок
				if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));//и сердечко


				s_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

				window.draw(s_map);//рисуем квадратики на экран
			}

		p.update(time);
		viewmap(time);//функция скроллинга карты, передаем ей время sfml
		changeview();//прикалываемся с камерой вида
		window.setView(view);//"оживляем" камеру в окне sfml

		
		

		std::ostringstream playerScoreString;    // объявили переменную
		std::ostringstream playerHealthString;
		playerHealthString << p.health;		//занесли в нее число здоровья, то есть формируем строку
		text.setString("Здоровье:" + playerHealthString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		text.setPosition(view.getCenter().x - 300, view.getCenter().y - 270);//задаем позицию текста, отступая от центра камеры
		text.setFillColor(sf::Color::Red);
		window.draw(text);//рисую этот текст

		playerScoreString << p.playerScore;		//занесли в нее число очков, то есть формируем строку
		text.setString("Собрано Руды:" + playerScoreString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		text.setPosition(view.getCenter().x - 300, view.getCenter().y - 250);//задаем позицию текста, отступая от центра камеры
		window.draw(text);//рисую этот текст
		
		if (p.Game)
		{
			gameTime = gameTimeClock.getElapsedTime().asSeconds();
			sound4.play();
		}
		else { if (time >= 5) { exit(1); } }

		if (p.life)
		{
			gameTime = gameTimeClock.getElapsedTime().asSeconds();
			sound3.play();
		}

		else { view.rotate(0.13); view.zoom(1.0006f); }//игровое время 

		window.draw(p.sprite);
		window.display();
	}

	return 0;
}
