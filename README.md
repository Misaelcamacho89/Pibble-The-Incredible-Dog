## 🛠️ Requisitos

- Compilador de C++ (recomendado: [MinGW-w64](https://www.mingw-w64.org/) o [w64devkit](https://github.com/skeeto/w64devkit))
- Librería [raylib](https://www.raylib.com/) instalada

## 🚀 Cómo compilar y ejecutar

1. Clona el repositorio:
   ```bash
   git clone https://github.com/Misaelcamacho89/Pibble-The-Game.git
   cd Pibble-The-Game
   ```

2. Compila el proyecto (ajusta las rutas `-I` y `-L` según dónde tengas instalado raylib en tu sistema):
   ```bash
   g++ pibble.cpp -o pibble.exe -I C:\raylib\include -L C:\raylib\lib -lraylib -lopengl32 -lgdi32 -lwinmm
   ```

   En Linux/Mac, el comando típico es:
   ```bash
   g++ pibble.cpp -o pibble -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
   ```

3. Ejecuta el programa:
   ```bash
   .\pibble.exe      # Windows
   ./pibble          # Linux/Mac
   ```

> ⚠️ Asegúrate de que la carpeta `imagenes/` esté en la misma ubicación que el ejecutable, ya que ahí se cargan los sprites de Pibble.

## 📁 Estructura del proyecto

```
Pibble-The-Game/
├── pibble.cpp        # Código fuente principal
├── imagenes/          # Sprites de estados y reacciones
└── README.md
```

## 📚 Contexto académico

Proyecto desarrollado para la materia de **Teoría de la Computación** (ICOM), como aplicación práctica del modelado de autómatas finitos con salida (Máquinas de Mealy).
