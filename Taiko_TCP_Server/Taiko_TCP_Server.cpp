#undef UNICODE
#include "stdafx.h"

#define WIN32_LEAN_AND_MEAN
#define WINVER 0x0500
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 1//512
#define DEFAULT_PORT "6113"

int __cdecl main(void)
{	
	INPUT ip;
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	do{
		// Accept a client socket
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}

		// No longer need server socket
		//closesocket(ListenSocket);

		// Receive until the peer shuts down the connection
		do {

			iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
			if (iResult > 0) {
				recvbuf[1] = '\0';
				/*for (int i = recvbuflen; i >= 1; i--)
				{
					if (recvbuf[i] == '\n' && recvbuf[i - 1] == '\r')
					{
						recvbuf[i - 1] = '\0';
						break;
					}
				}*/
				if (recvbuf[0] == *"Z"){
					// Set up a generic keyboard event.
					ip.type = INPUT_KEYBOARD;
					ip.ki.wScan = 0; // hardware scan code for key
					ip.ki.time = 0;
					ip.ki.dwExtraInfo = 0;

					// Press the "Z" key
					ip.ki.wVk = 0x5A; // virtual-key code for the "a" key
					ip.ki.dwFlags = 0; // 0 for key press
					SendInput(1, &ip, sizeof(INPUT));

					// Release the "Z" key
					ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
					SendInput(1, &ip, sizeof(INPUT));
					printf("Hey It's 'Z'");
				}if (recvbuf[0] == *"X"){
					// Set up a generic keyboard event.
					ip.type = INPUT_KEYBOARD;
					ip.ki.wScan = 0; // hardware scan code for key
					ip.ki.time = 0;
					ip.ki.dwExtraInfo = 0;

					// Press the "X" key
					ip.ki.wVk = 0x58; // virtual-key code for the "a" key
					ip.ki.dwFlags = 0; // 0 for key press
					SendInput(1, &ip, sizeof(INPUT));

					// Release the "X" key
					ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
					SendInput(1, &ip, sizeof(INPUT));
					printf("Hey It's 'X'");
				}if (recvbuf[0] == *"C"){
					// Set up a generic keyboard event.
					ip.type = INPUT_KEYBOARD;
					ip.ki.wScan = 0; // hardware scan code for key
					ip.ki.time = 0;
					ip.ki.dwExtraInfo = 0;

					// Press the "C" key
					ip.ki.wVk = 0x43; // virtual-key code for the "a" key
					ip.ki.dwFlags = 0; // 0 for key press
					SendInput(1, &ip, sizeof(INPUT));

					// Release the "C" key
					ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
					SendInput(1, &ip, sizeof(INPUT));
					printf("Hey It's 'C'");
				}if (recvbuf[0] == *"V"){
					// Set up a generic keyboard event.
					ip.type = INPUT_KEYBOARD;
					ip.ki.wScan = 0; // hardware scan code for key
					ip.ki.time = 0;
					ip.ki.dwExtraInfo = 0;

					// Press the "V" key
					ip.ki.wVk = 0x56; // virtual-key code for the "a" key
					ip.ki.dwFlags = 0; // 0 for key press
					SendInput(1, &ip, sizeof(INPUT));

					// Release the "V" key
					ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
					SendInput(1, &ip, sizeof(INPUT));
					printf("Hey It's 'V'");
				}
				//printf("\n Data: %s \n", recvbuf);
				//printf("Bytes received: %d\n", iResult);

				// Echo the buffer back to the sender
				iSendResult = send(ClientSocket, recvbuf, iResult, 0);
				if (iSendResult == SOCKET_ERROR) {
					printf("send failed with error: %d\n", WSAGetLastError());
					closesocket(ClientSocket);
					WSACleanup();
					system("pause");
					return 1;
				}
				//printf("Bytes sent: %d\n", iSendResult);
			}
			else if (iResult == 0)
				printf("Connection closing...\n");
			else  {
				printf("recv failed with error: %d\n", WSAGetLastError());
				//closesocket(ClientSocket);
				//WSACleanup();
				return 1;
			}

		} while (iResult > 0);
	} while (true);



	// shutdown the connection since we're done
	/*iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();*/
	system("pause");
	return 0;
}