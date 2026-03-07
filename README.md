# Cartesio

A lightweight C/C++ application that parses and renders mathematical functions on a Cartesian plane in real time, built with [raylib](https://www.raylib.com/) and [muParser](https://beltoforion.de/en/muparser/).

## Features

- Real-time rendering of mathematical functions on a Cartesian plane
- Dynamic function parsing from string input (e.g. `sin(x)`, `x^2 + 2*x - 1`)
- Zoomable and pannable viewport
- Axis and grid rendering

## Dependencies

| Library | Purpose |
|---|---|
| [raylib](https://www.raylib.com/) | Window creation & 2D rendering |
| [muParser](https://beltoforion.de/en/muparser/) | Mathematical expression parsing |

## Building

Make sure you have **raylib** and **muParser** installed, then:

```bash
# coming soon
```

## Usage

```bash
./cartesio
```

Enter a mathematical expression when prompted (or edit it directly in the source), and the function will be plotted on the Cartesian plane.

**Example expressions:**
```
sin(x)
x^2 - 3*x + 2
cos(x) * x
exp(-x^2)
```

## License

Do whatever you want with it.
