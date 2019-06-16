# unix-webdev-tools
Useful programs for web developer on *nix machine

## print-css
Prints css code in line based format (still valid CSS but more grep compatible). To compile C++11 is required.

Usage:
- ``print-css <filename>.css`` - prints CSS from ``filename``
- ``print-css -`` - prints CSS from ``stdin``
### Example:
Input css file:
```css
@import url('https://fonts.googleapis.com/css?family=Roboto&display=swap');

body {
  margin: 0;
  padding: 0;
  background-color: black;
}

h1 {
  text-align: center;
  color: greenyellow;
}
```
Program output:
```css
@import url('https://fonts.googleapis.com/css?family=Roboto&display=swap');
body { margin: 0; }
body { padding: 0; }
body { background-color: black; }
h1 { text-align: center; }
h1 { color: greenyellow; }
```
