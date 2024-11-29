#include "Personaje.h"

Personaje::Personaje(sf::Sprite sprite, int tipo, const sf::Vector2f& posicion)
    : sprite(sprite), tipo(tipo), posicion(posicion) {
    this->sprite.setPosition(posicion); 
}

sf::Sprite& Personaje::getSprite() {
    return sprite;
}

const sf::Sprite& Personaje::getSprite() const {
    return sprite;
}

int Personaje::getTipo() const {
    return tipo;
}

sf::Clock& Personaje::getReloj() {
    return reloj;
}

sf::Vector2f Personaje::getPosicion() const {
    return posicion;
}

void Personaje::setSprite(const sf::Sprite& nuevoSprite) {
    sprite = nuevoSprite;
}

void Personaje::setTipo(int nuevoTipo) {
    tipo = nuevoTipo;
}

void Personaje::setPosicion(const sf::Vector2f& nuevaPosicion) {
    posicion = nuevaPosicion;
    sprite.setPosition(nuevaPosicion);
}

void Personaje::reiniciarReloj() {
    reloj.restart();
}
