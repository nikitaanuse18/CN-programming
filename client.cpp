#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main()
{
    char buf[512];
    int sckfd;
    struct sockaddr_in serv_addr;
    ssize_t sent;

    // Create UDP socket
    sckfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sckfd < 0) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    // Initialize server address
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1500);

    cout << "UDP Client started." << endl;

    while (true) {
        cout << "Enter message (x to quit): ";
        cout.flush();

        if (!cin.getline(buf, sizeof(buf)))
            break;

        sent = sendto(sckfd, buf, strlen(buf), 0,
                      (struct sockaddr *)&serv_addr,
                      sizeof(serv_addr));

        if (sent < 0) {
            perror("Send failed");
            break;
        }

        cout << "Message sent." << endl;

        if (strcmp(buf, "x") == 0)
            break;
    }

    close(sckfd);
    cout << "Client closed." << endl;

    return 0;
}