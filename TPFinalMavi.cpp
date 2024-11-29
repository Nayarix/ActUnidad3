#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>
#include <string>
#include "Personaje.h"

using namespace sf;


std::vector<Vector2f> obtenerPosicionesVentanas() {
    return {
        {80, 240},
        {5, 240},
        {205, 170},
        {290, 170},
        {469, 170},
        {550, 170},
        {5, 370},
        {205, 340},
        {290, 340},
        {470, 340},
        {555, 340},
        {380, 57}
    };
}


void mostrarInstrucciones(RenderWindow& ventana, Font& font) {
    Text titulo("Como Jugar", font, 48);
    titulo.setFillColor(Color::White);
    titulo.setPosition(ventana.getSize().x / 2 - titulo.getGlobalBounds().width / 2, 50);

    std::string textoInstrucciones =
        "Objetivo del Juego:\n\n"
        "Dispara a los enemigos antes de que te alcancen.\n"
        "No dispares a los inocentes, perderas una vida si lo haces.\n\n"
        "Controles:\n"
        "Mueve la mira con el mouse.\n"
        "Dispara con el boton izquierdo del mouse.\n\n"
        "Reglas:\n"
        " - Tienes 3 vidas.\n"
        " - Sin limite de balas.\n"
        " - Tu puntaje depende de enemigos abatidos e inocentes fallados.\n\n"
        "Buena suerte y diviertete!";

    Text instrucciones(textoInstrucciones, font, 20);
    instrucciones.setFillColor(Color::White);
    instrucciones.setPosition(50, 150);

    Text botonVolver("Volver", font, 30);
    botonVolver.setFillColor(Color::Green);
    botonVolver.setPosition(ventana.getSize().x / 2 - botonVolver.getGlobalBounds().width / 2, 500);

    while (ventana.isOpen()) {
        Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == Event::Closed) {
                ventana.close();
                return;
            }
            if (evento.type == Event::MouseButtonPressed) {
                Vector2f mousePos = ventana.mapPixelToCoords(Mouse::getPosition(ventana));
                if (botonVolver.getGlobalBounds().contains(mousePos)) {
                    return; 
                }
            }
        }

        ventana.clear();
        ventana.draw(titulo);
        ventana.draw(instrucciones);
        ventana.draw(botonVolver);
        ventana.display();
    }
}


bool mostrarMenu(RenderWindow& ventana, Font& font) {
    Text titulo("Juego de Disparos", font, 48);
    titulo.setFillColor(Color::White);
    titulo.setPosition(ventana.getSize().x / 2 - titulo.getGlobalBounds().width / 2, 50);

    Text botonIniciar("Iniciar Juego", font, 36);
    botonIniciar.setFillColor(Color::Green);
    botonIniciar.setPosition(ventana.getSize().x / 2 - botonIniciar.getGlobalBounds().width / 2, 200);

    Text botonInstrucciones("Como Jugar", font, 36);
    botonInstrucciones.setFillColor(Color::Blue);
    botonInstrucciones.setPosition(ventana.getSize().x / 2 - botonInstrucciones.getGlobalBounds().width / 2, 300);

    Text botonSalir("Salir", font, 36);
    botonSalir.setFillColor(Color::Red);
    botonSalir.setPosition(ventana.getSize().x / 2 - botonSalir.getGlobalBounds().width / 2, 400);

    while (ventana.isOpen()) {
        Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == Event::Closed) {
                ventana.close();
                return false;
            }
            if (evento.type == Event::MouseButtonPressed) {
                Vector2f mousePos = ventana.mapPixelToCoords(Mouse::getPosition(ventana));
                if (botonIniciar.getGlobalBounds().contains(mousePos)) {
                    return true;
                }
                if (botonInstrucciones.getGlobalBounds().contains(mousePos)) {
                    mostrarInstrucciones(ventana, font); 
                }
                if (botonSalir.getGlobalBounds().contains(mousePos)) {
                    ventana.close();
                    return false;
                }
            }
        }

        ventana.clear();
        ventana.draw(titulo);
        ventana.draw(botonIniciar);
        ventana.draw(botonInstrucciones);
        ventana.draw(botonSalir);
        ventana.display();
    }
    return false;
}


void mostrarPantallaFinal(RenderWindow& ventana, Font& font, int puntaje) {
    Text gameOver("GAME OVER", font, 48);
    gameOver.setFillColor(Color::Red);
    gameOver.setPosition(ventana.getSize().x / 2 - gameOver.getGlobalBounds().width / 2, 100);

    Text textoPuntaje("Puntaje final: " + std::to_string(puntaje), font, 36);
    textoPuntaje.setFillColor(Color::White);
    textoPuntaje.setPosition(ventana.getSize().x / 2 - textoPuntaje.getGlobalBounds().width / 2, 250);

    Text botonSalir("Salir", font, 36);
    botonSalir.setFillColor(Color::Red);
    botonSalir.setPosition(ventana.getSize().x / 2 - botonSalir.getGlobalBounds().width / 2, 400);

    while (ventana.isOpen()) {
        Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == Event::Closed) {
                ventana.close();
            }
            if (evento.type == Event::MouseButtonPressed) {
                Vector2f mousePos = ventana.mapPixelToCoords(Mouse::getPosition(ventana));
                if (botonSalir.getGlobalBounds().contains(mousePos)) {
                    ventana.close();
                    return;
                }
            }
        }

        ventana.clear();
        ventana.draw(gameOver);
        ventana.draw(textoPuntaje);
        ventana.draw(botonSalir);
        ventana.display();
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

 
    RenderWindow ventana(VideoMode(800, 600), "Juego de Disparos");
    ventana.setFramerateLimit(60);

    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }

 
    if (!mostrarMenu(ventana, font)) {
        return 0;
    }

 
    Texture fondoTexture, enemigo1Texture, enemigo2Texture, inocente1Texture, inocente2Texture, punteroTexture, bangTexture;
    if (!fondoTexture.loadFromFile("Fondo para Tp Final Modelado de Algoritmos Version Final.jpg") ||
        !enemigo1Texture.loadFromFile("enemigo1png.png") ||
        !enemigo2Texture.loadFromFile("enemigo2png.png") ||
        !inocente1Texture.loadFromFile("inocente1png.png") ||
        !inocente2Texture.loadFromFile("inocente2png.png") ||
        !punteroTexture.loadFromFile("crosshair.png") ||
        !bangTexture.loadFromFile("bangpng.png")) {
        return -1;
    }

   
    Sprite fondoSprite(fondoTexture);
    fondoSprite.setScale(
        static_cast<float>(ventana.getSize().x) / fondoTexture.getSize().x,
        static_cast<float>(ventana.getSize().y) / fondoTexture.getSize().y
    );

    
    Sprite punteroSprite(punteroTexture);
    punteroSprite.setOrigin(punteroTexture.getSize().x / 2, punteroTexture.getSize().y / 2);
    punteroSprite.setScale(0.25f, 0.25f);

    Sprite bangSprite(bangTexture);
    bangSprite.setScale(0.3f, 0.3f);

   
    std::vector<Sprite> personajesSprites = { Sprite(enemigo1Texture), Sprite(enemigo2Texture), Sprite(inocente1Texture), Sprite(inocente2Texture) };
    for (auto& sprite : personajesSprites) {
        sprite.setScale(0.05f, 0.1f);
    }

    auto posicionesVentanas = obtenerPosicionesVentanas();

    
    std::vector<Personaje> personajesActivos;
    std::set<int> posicionesOcupadas;

    
    int enemigosAbatidos = 0, inocentesAbatidos = 0, vidas = 3;

    for (int i = 0; i < 2; ++i) {
        int tipo = rand() % personajesSprites.size();
        int indicePosicion;
        do {
            indicePosicion = rand() % posicionesVentanas.size();
        } while (posicionesOcupadas.count(indicePosicion) > 0);

        posicionesOcupadas.insert(indicePosicion);
        personajesActivos.emplace_back(personajesSprites[tipo], tipo, posicionesVentanas[indicePosicion]);
    }

    Clock tiempoTotal, relojBang;
    bool mostrarBang = false;

    
    Text textoEnemigosAbatidos("Enemigos Abatidos: 0", font, 24);
    textoEnemigosAbatidos.setFillColor(Color::White);
    textoEnemigosAbatidos.setPosition(200, 550);

    Text textoVidas("Vidas: 3", font, 24);
    textoVidas.setFillColor(Color::Red);
    textoVidas.setPosition(510, 550);


    while (ventana.isOpen()) {
        Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == Event::Closed) {
                ventana.close();
            }
            if (evento.type == Event::MouseButtonPressed && evento.mouseButton.button == Mouse::Left) {
                Vector2f mousePos = ventana.mapPixelToCoords(Mouse::getPosition(ventana));
                for (auto& personaje : personajesActivos) {
                    if (personaje.getSprite().getGlobalBounds().contains(mousePos)) {
                        if (personaje.getTipo() == 0 || personaje.getTipo() == 1) {
                            enemigosAbatidos++;
                        }
                        else {
                            inocentesAbatidos++;
                            vidas--;
                        }

                        posicionesOcupadas.erase(std::find(posicionesVentanas.begin(), posicionesVentanas.end(), personaje.getPosicion()) - posicionesVentanas.begin());

                        int indicePosicion;
                        do {
                            indicePosicion = rand() % posicionesVentanas.size();
                        } while (posicionesOcupadas.count(indicePosicion) > 0);

                        posicionesOcupadas.insert(indicePosicion);
                        personaje.setTipo(rand() % personajesSprites.size());
                        personaje.setSprite(personajesSprites[personaje.getTipo()]);
                        personaje.setPosicion(posicionesVentanas[indicePosicion]);
                        personaje.reiniciarReloj();
                    }
                }
            }
        }

        int cantidadMaximaPersonajes = 2;
        if (tiempoTotal.getElapsedTime().asSeconds() > 80) {
            cantidadMaximaPersonajes = 5;
        }
        else if (tiempoTotal.getElapsedTime().asSeconds() > 60) {
            cantidadMaximaPersonajes = 4;
        }
        else if (tiempoTotal.getElapsedTime().asSeconds() > 20) {
            cantidadMaximaPersonajes = 3;
        }

        while (personajesActivos.size() < cantidadMaximaPersonajes) {
            int tipoNuevo = rand() % personajesSprites.size();
            int indicePosicion;
            do {
                indicePosicion = rand() % posicionesVentanas.size();
            } while (posicionesOcupadas.count(indicePosicion) > 0);

            posicionesOcupadas.insert(indicePosicion);
            personajesActivos.emplace_back(personajesSprites[tipoNuevo], tipoNuevo, posicionesVentanas[indicePosicion]);
        }

        for (auto& personaje : personajesActivos) {
            if (personaje.getReloj().getElapsedTime().asSeconds() > 2.5f) {
                if (personaje.getTipo() == 0 || personaje.getTipo() == 1) {
                    vidas--;
                    mostrarBang = true;
                    bangSprite.setPosition(personaje.getPosicion());
                    relojBang.restart();
                }

                posicionesOcupadas.erase(std::find(posicionesVentanas.begin(), posicionesVentanas.end(), personaje.getPosicion()) - posicionesVentanas.begin());

                int indicePosicion;
                do {
                    indicePosicion = rand() % posicionesVentanas.size();
                } while (posicionesOcupadas.count(indicePosicion) > 0);

                posicionesOcupadas.insert(indicePosicion);
                personaje.setTipo(rand() % personajesSprites.size());
                personaje.setSprite(personajesSprites[personaje.getTipo()]);
                personaje.setPosicion(posicionesVentanas[indicePosicion]);
                personaje.reiniciarReloj();
            }
        }

        if (mostrarBang && relojBang.getElapsedTime().asSeconds() > 1.0f) {
            mostrarBang = false;
        }

        punteroSprite.setPosition(ventana.mapPixelToCoords(Mouse::getPosition(ventana)));

  
        textoEnemigosAbatidos.setString("Enemigos Abatidos: " + std::to_string(enemigosAbatidos));
        textoVidas.setString("Vidas: " + std::to_string(vidas));

     
        ventana.clear();
        ventana.draw(fondoSprite);
        for (const auto& personaje : personajesActivos) {
            ventana.draw(personaje.getSprite());
        }
        if (mostrarBang) {
            ventana.draw(bangSprite);
        }
        ventana.draw(punteroSprite);
        ventana.draw(textoEnemigosAbatidos);
        ventana.draw(textoVidas);
        ventana.display();

        if (vidas <= 0) {
            int puntajeFinal = enemigosAbatidos - (inocentesAbatidos * 2);
            mostrarPantallaFinal(ventana, font, puntajeFinal);
            return 0;
        }
    }

    return 0;
}
