IoT-Based Home Automation System with Web Server and IR Control
Overview

This project implements an IoT-based home automation system that allows users to control multiple appliances remotely via a web server and locally using an IR remote. It combines Wi-Fi connectivity and infrared communication for flexible control.

Features

Web Server Control: Turn devices ON/OFF through a responsive web interface.

IR Remote Control: Control appliances without an internet connection using an infrared remote.

Fail-Safe Operation: Automatically switches to IR control if Wi-Fi is unavailable.

Multiple Device Control: Supports controlling multiple relays for home appliances.

Hardware Components

ESP8266 NodeMCU

IR Receiver Module

Relays

Power Supply

Jumper Wires

Software Requirements

Arduino IDE

ESP8266 Board Package

Libraries: ESP8266WiFi, ESP8266WebServer, IRremote

How It Works

When powered on, the ESP8266 connects to the configured Wi-Fi network and hosts a web server.

The user can access the server via any browser to control appliances.

If Wi-Fi is unavailable, the system defaults to IR remote control.

Installation

Install Arduino IDE and required libraries.

Upload the code to the ESP8266 NodeMCU.

Configure your SSID and password in the code.

Connect the hardware as specified in the circuit diagram.

Access the web interface using the ESP8266 IP address.

Future Enhancements

Add mobile app integration.

Include voice control support.

Enable real-time device status monitoring.
