#version 330 core

in vec4 exColor;
out vec4 outColor;

uniform vec4 uColor;

//como os vértices são brancos, a cor final passa a ser o uColor (que é controlado no drawScene)
void main(void) {
    outColor = exColor * uColor;
}
