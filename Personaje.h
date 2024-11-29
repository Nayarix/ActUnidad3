#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <SFML/Graphics.hpp>

class Personaje {
private:
    sf::Sprite sprite;
    int tipo;
    sf::Clock reloj;
    sf::Vector2f posicion;

public:
    Personaje(sf::Sprite sprite, int tipo, const sf::Vector2f& posicion);

    sf::Sprite& getSprite();              
    const sf::Sprite& getSprite() const;   

    int getTipo() const;               
    sf::Clock& getReloj();               
    sf::Vector2f getPosicion() const;      

    void setSprite(const sf::Sprite& nuevoSprite);
    void setTipo(int nuevoTipo);
    void setPosicion(const sf::Vector2f& nuevaPosicion);
    void reiniciarReloj();
};

#endif 
