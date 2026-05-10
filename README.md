# 🛒 DATAMAZON CLI

> Simulación simplificada de una plataforma de e-commerce (estilo Amazon) desarrollada como proyecto universitario para el curso **Estructura de Datos Avanzadas** — UPC.

---

## 👥 Integrantes

| Nombre         | GitHub                                                 |
| -------------- | ------------------------------------------------------ |
| André Sanchez  | [@Andzzio](https://github.com/Andzzio)                 |
| Leonardo Primo | [@xZoomL](https://github.com/xZoomL)                   |
| Josue Ochoa    | [@ShahrukOchoa](https://github.com/shahrukhochoa8-oss) |

---

## 🎯 Objetivo

Implementar las estructuras de datos vistas en el curso dentro de un sistema funcional que simule las operaciones principales de un marketplace: búsqueda de productos, gestión de inventario, historial de compras y recomendaciones.

---

## 🏗️ Estructuras de datos implementadas

> _Lista de TDA (Tipos de Datos Abstractos) desarrollados desde cero (sin usar la STL):_

| Estructura                    | Uso en el sistema                                                                                 |
| ----------------------------- | ------------------------------------------------------------------------------------------------- |
| **SimpleList** (Lista Simple) | Gestión principal de Catálogos (Clientes, Proveedores, Almacenes, Reseñas, Categorías y Cupones). |
| **DoubleList** (Lista Doble)  | Gestión bidireccional del Catálogo Principal de Productos y Detalles de Pedido (`OrderDetail`).   |
| **Stack** (Pila - LIFO)       | Gestión del **Historial de Carrito** del cliente (el último agregado es el primero en verse).     |
| **Queue** (Cola - FIFO)       | Gestión de la **Cola de Pedidos** (los pedidos se procesan en el orden estricto de llegada).      |

---

## ✨ Funcionalidades Destacadas

- **Diseño Visual Profesional**: Interfaz construida con **Códigos de Escape ANSI** (colores dinámicos) y tabulación avanzada (`<iomanip>`) para dibujar tarjetas gráficas y tablas perfectas que emulan un Software SaaS real.
- **Buscador Reactivo (Fuzzy Search)**: Sistema de búsqueda de productos inteligente en tiempo real, implementado usando `_getch()`, que filtra y redibuja resultados letra por letra conforme el usuario escribe.
- **Robustez (Anti-Crash)**: Sistema custom de validación (`InputValidator`) a través de templates de C++ para limpiar el buffer y prevenir bucles infinitos por errores de tipeo del usuario.
- **+15 Entidades de Dominio**: Simulación completa del modelo de negocio incluyendo Generación de Facturas (`Invoice`), Cupones de descuento, Métodos de Pago y Guías de Envío Remitidas (`Shipment`).

---

## 🛠️ Stack

- **Lenguaje:** C++
- **UI:** CLI
- **IDE:** Visual Studio

---

## ⚙️ Requisitos

- Windows 10 / 11
- Visual Studio 2022 con el workload **Desktop development with C++**
- .NET Framework 4.7.2 o superior

---

## 🚀 Cómo correr el proyecto

```sh
# 1. Clona el repositorio
git clone https://github.com/Andzzio/datamazon.git

# 2. Abre la solución en Visual Studio
# Archivo → Abrir → Proyecto/Solución → datamazon.sln

# 3. Compila y ejecuta (F5)
```

---

## 📁 Estructura del Proyecto

El código está estructurado bajo los principios de POO:

- `DatamazonCLI.cpp`: Archivo principal `main()` con el loop del flujo general.
- `MenuAdmin.h` / `MenuClient.h`: Capas de presentación y manejo de lógica de interfaz.
- `ConsoleUI.h` / `InputValidator.h`: Clases estáticas utilitarias para el diseño gráfico ANSI y la limpieza de entradas de terminal.
- `Entity.h`: Clase abstracta padre de la cual heredan las demás (+15 Entidades del modelo).

---

## 📸 Screenshots

> _Se agregarán capturas de la interfaz cuando esté lista._

---

## 📄 Licencia

Proyecto académico — **UPC, Estructura de Datos Avanzadas**.  
No licenciado para uso comercial.
