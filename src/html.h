#include "main.h"

void viewHTML(WiFiClient client) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();
    client.print("<style>");
    client.print(".container {margin: 0 auto; text-align: center; margin-top: 100px;}");
    client.print("button {color: white; width: 100px; height: 100px;");
    client.print("border-radius: 50%; margin: 20px; border: none; font-size: 20px; outline: none; transition: all 0.2s;}");
    client.print(".red{background-color: rgb(196, 39, 39);}");
    client.print(".green{background-color: rgb(39, 121, 39);}");
    client.print(".blue {background-color: rgb(5, 87, 180);}");
    client.print(".off{background-color: grey;}");
    client.print("button:hover{cursor: pointer; opacity: 0.7;}");
    client.print("</style>");
    client.print("<div class='container'>");
    client.print("<button class='red' type='submit' onmousedown='location.href=\"/RH\"'>ON</button>");
    client.print("<button class='off' type='submit' onmousedown='location.href=\"/RL\"'>OFF</button><br>");
    client.print("<button class='green' type='submit' onmousedown='location.href=\"/GH\"'>ON</button>");
    client.print("<button class='off' type='submit' onmousedown='location.href=\"/GL\"'>OFF</button><br>");
    client.print("<button class='blue' type='submit' onmousedown='location.href=\"/BH\"'>ON</button>");
    client.print("<button class='off' type='submit' onmousedown='location.href=\"/BL\"'>OFF</button>");
    client.println();
    client.print("</div>");
    client.println();
    client.print("<div class='container'>");
    client.print("Temperatura: ");
    client.print(temperature);
    client.print(" C ");
    client.println();
    client.print("</div>");
    client.println();
    client.print("<div class='container'>");
    client.println("Acelerometro: ");
    client.print("X: "); client.print(posaX); client.print("  ");
    client.print("Y: "); client.print(posaY); client.print("  ");
    client.print("Z: "); client.print(posaZ); client.print("  ");
    client.print("</div>");
    client.println();
    client.print("<div class='container'>");
    client.println("Giroscopio: ");
    client.print("X: "); client.print(posgX); client.print("  ");
    client.print("Y: "); client.print(posgY); client.print("  ");
    client.print("Z: "); client.print(posgZ); client.print("  ");
    client.print("</div>");
}