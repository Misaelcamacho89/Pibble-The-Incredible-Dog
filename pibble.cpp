#include "raylib.h"
#include <string>

enum Estado { FELIZ, TRISTE, ENOJADO, ABURRIDO, SEDIENTO, ENAMORADO, ASUSTADO, HAMBRIENTO, INCOMODO, AGOTADO, NUM_ESTADOS };
enum Entrada { ACARICIAR, GOLPEAR, ABRAZAR, DAR_COMIDA, CONSOLAR, JUGAR, OBSERVAR, BESAR, DORMIR, DAR_AGUA, NUM_ENTRADAS };

const int NUM_SALIDAS_MEALY = 20;

std::string textosSalida[NUM_SALIDAS_MEALY] = {
    "Sonrie", "Llora", "Se emociona", "Piensa en comida", "Se calma",
    "Juega", "Te mira", "Sonroja", "Se duerme", "Piensa en agua",
    "Se voltea", "Grune", "Se aleja", "Te ignora", "Saca la lengua",
    "Se enoja", "Bosteza", "Muestra ojos de corazon", "Tiembla", "Se acerca"
};

std::string nombresEstados[NUM_ESTADOS] = {
    "FELIZ", "TRISTE", "ENOJADO", "ABURRIDO", "SEDIENTO",
    "ENAMORADO", "ASUSTADO", "HAMBRIENTO", "INCOMODO", "AGOTADO"
};

int matrizF[NUM_ESTADOS][NUM_ENTRADAS] = {
    { 8, 2, 0, 4, 3, 9, 8, 5, 1, 7 },
    { 0, 6, 0, 1, 0, 8, 6, 8, 9, 1 }, 
    { 8, 1, 0, 7, 0, 9, 8, 4, 2, 6 },
    { 3, 3, 3, 3, 3, 0, 3, 3, 3, 3 }, 
    { 4, 4, 4, 4, 4, 4, 4, 4, 4, 0 }, 
    { 5, 1, 5, 8, 5, 4, 8, 5, 2, 8 },
    { 0, 6, 5, 4, 0, 9, 8, 5, 2, 3 }, 
    { 7, 7, 7, 0, 7, 7, 7, 7, 7, 7 }, 
    { 8, 1, 0, 8, 0, 8, 8, 6, 1, 8 },
    { 1, 6, 5, 4, 2, 9, 8, 3, 0, 7 }  
};

int matrizG[NUM_ESTADOS][NUM_ENTRADAS] = {
    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9 }, 
    {  4,  1,  7,  3,  0,  2,  6,  7,  1,  9 }, 
    { 10, 11, 12,  3,  4,  5, 13, 14,  8,  9 },
    { 10, 15, 10,  3, 10,  5, 16, 10,  8,  9 }, 
    { 10,  1, 10,  3, 10, 10, 13, 10,  8,  4 }, 
    {  7,  1, 17,  3,  7,  5,  6, 17,  8,  9 },
    {  4, 18, 19,  3,  4, 10,  6,  7,  1,  9 }, 
    { 10,  1, 10,  4, 10, 10, 13, 10,  8,  9 }, 
    { 12,  1, 10,  3,  4, 10, 13,  7,  8,  9 },
    {  4,  1,  7,  3,  4, 10,  6,  7,  8,  9 }  
};

enum Pantalla { PORTADA, JUGANDO };

int main() {
    InitWindow(800, 600, "Pibble: the incredible dog - Proyecto ICOM");
    SetTargetFPS(60);

    Pantalla pantallaActual = PORTADA;
    Rectangle btnJugar = { 300, 480, 200, 60 };

    std::string nombresEntradas[NUM_ENTRADAS] = {
        "Acariciar", "Golpear", "Abrazar", "Comida", "Consolar", 
        "Jugar", "Observar", "Besar", "Dormir", "Agua"
    };

    Rectangle botones[NUM_ENTRADAS];
    int anchoBoton = 120, altoBoton = 40, espacioX = 20, espacioY = 15;
    int anchoFila = (5 * anchoBoton) + (4 * espacioX);
    int margenIzq = (800 - anchoFila) / 2; 

    for (int i = 0; i < NUM_ENTRADAS; i++) {
        botones[i] = { 
            (float)(margenIzq + (i % 5) * (anchoBoton + espacioX)), 
            (float)(470 + (i / 5) * (altoBoton + espacioY)), 
            (float)anchoBoton, (float)altoBoton 
        };
    }

    Texture2D texturaPortada = LoadTexture("imagenes/imagen_inicio.png");

    Texture2D texEstados[NUM_ESTADOS];
    for (int i = 0; i < NUM_ESTADOS; i++) {
        texEstados[i] = LoadTexture(TextFormat("imagenes/estado_%d.png", i));
    }

    Texture2D texSalidas[NUM_SALIDAS_MEALY];
    for (int i = 0; i < NUM_SALIDAS_MEALY; i++) {
        texSalidas[i] = LoadTexture(TextFormat("imagenes/salida_%d.png", i));
    }

    int estadoActual = FELIZ;
    int reaccionActual = 0;
    bool mostrandoReaccion = false;
    double tiempoReaccion = 0.0;

    Rectangle marcoMascota = {150, 50, 500, 380};

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        if (pantallaActual == PORTADA) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, btnJugar)) {
                pantallaActual = JUGANDO; 
            }
        } 
        else if (pantallaActual == JUGANDO) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !mostrandoReaccion) {
                for (int i = 0; i < NUM_ENTRADAS; i++) {
                    if (CheckCollisionPointRec(mouse, botones[i])) {
                        reaccionActual = matrizG[estadoActual][i]; 
                        estadoActual = matrizF[estadoActual][i];   
                        mostrandoReaccion = true;
                        tiempoReaccion = GetTime(); 
                    }
                }
            }

            if (mostrandoReaccion && (GetTime() - tiempoReaccion > 3.0)) {
                mostrandoReaccion = false;
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE); 

            if (pantallaActual == PORTADA) {
                DrawText("PIBBLE: THE INCREDIBLE DOG", 50, 80, 45, DARKGRAY);
                DrawText("Maquina de Mealy", 300, 140, 20, GRAY);
                
                if (texturaPortada.id > 0) {
                    float escalaPortada = 300.0f / texturaPortada.height; 
                    float posImgX = (800 - (texturaPortada.width * escalaPortada)) / 2;
                    DrawTextureEx(texturaPortada, { posImgX, 140 }, 0.0f, escalaPortada, WHITE);
                }

                Color colorBtn = CheckCollisionPointRec(mouse, btnJugar) ? BLUE : SKYBLUE;
                DrawRectangleRec(btnJugar, colorBtn); 
                DrawRectangleLinesEx(btnJugar, 3, DARKBLUE); 
                DrawText("INICIAR", btnJugar.x + 55, btnJugar.y + 18, 25, WHITE);

               
                const char* textoAutores = "Autores: Misael Camacho, Miguel, Sergio Anguiano";
                int tamAutores = 18;
                int anchoAutores = MeasureText(textoAutores, tamAutores);
                
                
                DrawText(textoAutores, (800 - anchoAutores) / 2, 560, tamAutores, DARKGRAY);
                
            }
            else if (pantallaActual == JUGANDO) {
                DrawText(TextFormat("ESTADO: %s", nombresEstados[estadoActual].c_str()), 160, 20, 20, DARKBLUE);

                DrawRectangleRounded(marcoMascota, 0.05f, 10, LIGHTGRAY);
                DrawRectangleRoundedLines(marcoMascota, 0.05f, 10, GRAY);

                Texture2D texturaActual;

                if (mostrandoReaccion) {
                    texturaActual = texSalidas[reaccionActual];
                    
                    const char* textoReaccion = TextFormat("Reacción: %s!", textosSalida[reaccionActual].c_str());
                    int anchoTexto = MeasureText(textoReaccion, 20);
                    DrawText(textoReaccion, marcoMascota.x + (marcoMascota.width - anchoTexto) / 2, 220, 20, BLACK);
                } else {
                    texturaActual = texEstados[estadoActual];
                    
                    const char* textoEstado = TextFormat("Sintiendose: %s", nombresEstados[estadoActual].c_str());
                    int anchoTexto = MeasureText(textoEstado, 20);
                    DrawText(textoEstado, marcoMascota.x + (marcoMascota.width - anchoTexto) / 2, 390, 20, WHITE);
                }

                int indiceImagen = mostrandoReaccion ? reaccionActual : estadoActual;
                float ajusteY = -40; 

                if (indiceImagen == 8) ajusteY = -55;
                else if (indiceImagen == 2 || indiceImagen == 7) ajusteY = -25;
                else if (indiceImagen == 3) ajusteY = -20;

                if (texturaActual.id > 0) { 
                    float escala = (marcoMascota.height * 1.0f) / texturaActual.height;
                    float posImageX = marcoMascota.x + (marcoMascota.width - (texturaActual.width * escala)) / 2;
                    float posImageY = marcoMascota.y + (marcoMascota.height - (texturaActual.height * escala)) / 2 + ajusteY;

                    DrawTextureEx(texturaActual, { posImageX, posImageY }, 0.0f, escala, WHITE);
                }

                for (int i = 0; i < NUM_ENTRADAS; i++) {
                    bool tocando = CheckCollisionPointRec(mouse, botones[i]);
                    Color colorFondo = (tocando && !mostrandoReaccion) ? GOLD : (mostrandoReaccion ? LIGHTGRAY : ORANGE); 
                    
                    DrawRectangleRec(botones[i], colorFondo);
                    DrawRectangleLinesEx(botones[i], 2, DARKBROWN);

                    int anchoTexto = MeasureText(nombresEntradas[i].c_str(), 15);
                    DrawText(nombresEntradas[i].c_str(), botones[i].x + (anchoBoton - anchoTexto) / 2, botones[i].y + 12, 15, BLACK);
                }
            }

        EndDrawing();
    }

    for (int i = 0; i < NUM_ESTADOS; i++) UnloadTexture(texEstados[i]);
    for (int i = 0; i < NUM_SALIDAS_MEALY; i++) UnloadTexture(texSalidas[i]);

    UnloadTexture(texturaPortada);
    CloseWindow(); 
    return 0;
}