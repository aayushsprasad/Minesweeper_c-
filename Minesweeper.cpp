#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>

class MineSweeper {
private:
    int fieldVisible[10][10] = { 0 };
    int fieldHidden[10][10] = { 0 };

public:
    void displayVisible(sf::RenderWindow& window, sf::Font& font);
    void displayHidden(sf::RenderWindow& window, sf::Font& font);
    void fixVisible(int i, int j);
    void fixNeighbours(int i, int j);
    bool playMove(int i, int j);
    void buildHidden();
    void setupField(int diff);
    bool checkWin();
    void startGame();
};

void MineSweeper::displayVisible(sf::RenderWindow& window, sf::Font& font) {
    window.clear(sf::Color::White);
    sf::RectangleShape cell(sf::Vector2f(30, 30));
    sf::Text text;

    text.setFont(font);
    text.setCharacterSize(24);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cell.setPosition(j * 30, i * 30);
            cell.setFillColor(sf::Color::Blue);
            window.draw(cell);

            if (fieldVisible[i][j] == 0) {
                text.setString("?");
            } else if (fieldVisible[i][j] == 50) {
                text.setString(" ");
            } else {
                text.setString(std::to_string(fieldVisible[i][j]));
            }

            text.setPosition(j * 30 + 5, i * 30 - 5);
            window.draw(text);
        }
    }
    window.display();
}

void MineSweeper::displayHidden(sf::RenderWindow& window, sf::Font& font) {
    window.clear(sf::Color::White);
    sf::RectangleShape cell(sf::Vector2f(30, 30));
    sf::Text text;

    text.setFont(font);
    text.setCharacterSize(24);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cell.setPosition(j * 30, i * 30);
            cell.setFillColor(sf::Color::Red);
            window.draw(cell);

            if (fieldHidden[i][j] == 0) {
                text.setString(" ");
            } else if (fieldHidden[i][j] == 100) {
                text.setString("X");
            } else {
                text.setString(std::to_string(fieldHidden[i][j]));
            }

            text.setPosition(j * 30 + 5, i * 30 - 5);
            window.draw(text);
        }
    }
    window.display();
}

void MineSweeper::fixVisible(int i, int j) {
    fieldVisible[i][j] = 50;
    if (i != 0) {
        fieldVisible[i - 1][j] = fieldHidden[i - 1][j];
        if (fieldVisible[i - 1][j] == 0) fieldVisible[i - 1][j] = 50;
        if (j != 0) {
            fieldVisible[i - 1][j - 1] = fieldHidden[i - 1][j - 1];
            if (fieldVisible[i - 1][j - 1] == 0) fieldVisible[i - 1][j - 1] = 50;
        }
    }
    if (i != 9) {
        fieldVisible[i + 1][j] = fieldHidden[i + 1][j];
        if (fieldVisible[i + 1][j] == 0) fieldVisible[i + 1][j] = 50;
        if (j != 9) {
            fieldVisible[i + 1][j + 1] = fieldHidden[i + 1][j + 1];
            if (fieldVisible[i + 1][j + 1] == 0) fieldVisible[i + 1][j + 1] = 50;
        }
    }
    if (j != 0) {
        fieldVisible[i][j - 1] = fieldHidden[i][j - 1];
        if (fieldVisible[i][j - 1] == 0) fieldVisible[i][j - 1] = 50;
        if (i != 9) {
            fieldVisible[i + 1][j - 1] = fieldHidden[i + 1][j - 1];
            if (fieldVisible[i + 1][j - 1] == 0) fieldVisible[i + 1][j - 1] = 50;
        }
    }
    if (j != 9) {
        fieldVisible[i][j + 1] = fieldHidden[i][j + 1];
        if (fieldVisible[i][j + 1] == 0) fieldVisible[i][j + 1] = 50;
        if (i != 0) {
            fieldVisible[i - 1][j + 1] = fieldHidden[i - 1][j + 1];
            if (fieldVisible[i - 1][j + 1] == 0) fieldVisible[i - 1][j + 1] = 50;
        }
    }
}

void MineSweeper::fixNeighbours(int i, int j) {
    srand(time(nullptr));
    int x = rand() % 4;

    fieldVisible[i][j] = fieldHidden[i][j];

    if (x == 0) {
        if (i != 0) {
            if (fieldHidden[i - 1][j] != 100) {
                fieldVisible[i - 1][j] = fieldHidden[i - 1][j];
                if (fieldVisible[i - 1][j] == 0)  fieldVisible[i - 1][j] = 50;
            }
        }
        if (j != 0) {
            if (fieldHidden[i][j - 1] != 100) {
                fieldVisible[i][j - 1] = fieldHidden[i][j - 1];
                if (fieldVisible[i][j - 1] == 0)  fieldVisible[i][j - 1] = 50;
            }

        }
        if (i != 0 && j != 0) {
            if (fieldHidden[i - 1][j - 1] != 100) {
                fieldVisible[i - 1][j - 1] = fieldHidden[i - 1][j - 1];
                if (fieldVisible[i - 1][j - 1] == 0)  fieldVisible[i - 1][j - 1] = 50;
            }

        }
    }
    else if (x == 1) {
        if (i != 0) {
            if (fieldHidden[i - 1][j] != 100) {
                fieldVisible[i - 1][j] = fieldHidden[i - 1][j];
                if (fieldVisible[i - 1][j] == 0)  fieldVisible[i - 1][j] = 50;
            }
        }
        if (j != 9) {
            if (fieldHidden[i][j + 1] != 100) {
                fieldVisible[i][j + 1] = fieldHidden[i][j + 1];
                if (fieldVisible[i][j + 1] == 0)  fieldVisible[i][j + 1] = 50;
            }

        }
        if (i != 0 && j != 9) {
            if (fieldHidden[i - 1][j + 1] != 100) {
                fieldVisible[i - 1][j + 1] = fieldHidden[i - 1][j + 1];
                if (fieldVisible[i - 1][j + 1] == 0)  fieldVisible[i - 1][j + 1] = 50;
            }
        }
    }
    else if (x == 2) {
        if (i != 9) {
            if (fieldHidden[i + 1][j] != 100) {
                fieldVisible[i + 1][j] = fieldHidden[i + 1][j];
                if (fieldVisible[i + 1][j] == 0)  fieldVisible[i + 1][j] = 50;
            }
        }
        if (j != 9) {
            if (fieldHidden[i][j + 1] != 100) {
                fieldVisible[i][j + 1] = fieldHidden[i][j + 1];
                if (fieldVisible[i][j + 1] == 0)  fieldVisible[i][j + 1] = 50;
            }

        }
        if (i != 9 && j != 9) {
            if (fieldHidden[i + 1][j + 1] != 100) {
                fieldVisible[i + 1][j + 1] = fieldHidden[i + 1][j + 1];
                if (fieldVisible[i + 1][j + 1] == 0)  fieldVisible[i + 1][j + 1] = 50;
            }
        }
    }
    else {
        if (i != 9) {
            if (fieldHidden[i + 1][j] != 100) {
                fieldVisible[i + 1][j] = fieldHidden[i + 1][j];
                if (fieldVisible[i + 1][j] == 0)  fieldVisible[i + 1][j] = 50;
            }
        }
        if (j != 0) {
            if (fieldHidden[i][j - 1] != 100) {
                fieldVisible[i][j - 1] = fieldHidden[i][j - 1];
                if (fieldVisible[i][j - 1] == 0)  fieldVisible[i][j - 1] = 50;
            }

        }
        if (i != 9 && j != 0) {
            if (fieldHidden[i + 1][j - 1] != 100) {
                fieldVisible[i + 1][j - 1] = fieldHidden[i + 1][j - 1];
                if (fieldVisible[i + 1][j - 1] == 0)  fieldVisible[i + 1][j - 1] = 50;
            }
        }
    }
}

bool MineSweeper::playMove(int i, int j) {
    if (i < 0 || i > 9 || j < 0 || j > 9 || fieldVisible[i][j] != 0) {
        std::cout << "\nIncorrect Input!!";
        return true;
    }

    if (fieldHidden[i][j] == 100) {
        std::cout << "Oops! You stepped on a mine!\n============GAME OVER============";
        return false;
    }
    else if (fieldHidden[i][j] == 0) {
        fixVisible(i, j);
    }
    else {
        fixNeighbours(i, j);
    }

    return true;
}

void MineSweeper::buildHidden() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            int cnt = 0;
            if (fieldHidden[i][j] != 100) {

                if (i != 0) {
                    if (fieldHidden[i - 1][j] == 100) cnt++;
                    if (j != 0) {
                        if (fieldHidden[i - 1][j - 1] == 100) cnt++;
                    }

                }
                if (i != 9) {
                    if (fieldHidden[i + 1][j] == 100) cnt++;
                    if (j != 9) {
                        if (fieldHidden[i + 1][j + 1] == 100) cnt++;
                    }
                }
                if (j != 0) {
                    if (fieldHidden[i][j - 1] == 100) cnt++;
                    if (i != 9) {
                        if (fieldHidden[i + 1][j - 1] == 100) cnt++;
                    }
                }
                if (j != 9) {
                    if (fieldHidden[i][j + 1] == 100) cnt++;
                    if (i != 0) {
                        if (fieldHidden[i - 1][j + 1] == 100) cnt++;
                    }
                }

                fieldHidden[i][j] = cnt;
            }
        }
    }
}

void MineSweeper::setupField(int diff) {
    int var = 0;
    while (var != 10) {
        srand(time(nullptr));
        int i = rand() % 10;
        int j = rand() % 10;
        fieldHidden[i][j] = 100;
        var++;
    }
    buildHidden();
}

bool MineSweeper::checkWin() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (fieldVisible[i][j] == 0) {
                if (fieldHidden[i][j] != 100) {
                    return false;
                }
            }
        }
    }
    return true;
}

void MineSweeper::startGame() {
    sf::RenderWindow window(sf::VideoMode(300, 300), "Minesweeper");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return;
    }

    setupField(1);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x / 30;
                int y = event.mouseButton.y / 30;
                if (!playMove(y, x)) {
                    displayHidden(window, font);
                    window.display();
                    sf::sleep(sf::seconds(2));
                    window.close();
                }
            }
        }
        displayVisible(window, font);
        if (checkWin()) {
            std::cout << "\n================You WON!!!================";
            displayHidden(window, font);
            window.display();
            sf::sleep(sf::seconds(2));
            window.close();
        }
    }
}

int main() {
    MineSweeper game;
    game.startGame();
    return 0;
}
