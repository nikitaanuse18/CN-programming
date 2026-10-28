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
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_len;
    ssize_t n;

    // Create UDP socket
    sckfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sckfd < 0) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    // Initialize server address
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(1500);

    // Bind socket
    if (bind(sckfd, (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) < 0) {
        perror("Bind failed");
        close(sckfd);
        return EXIT_FAILURE;
    }

    cout << "UDP Server waiting on port 1500..." << endl;

    while (true) {
        cli_len = sizeof(cli_addr);

        n = recvfrom(sckfd, buf, sizeof(buf) - 1, 0,
                     (struct sockaddr *)&cli_addr, &cli_len);

        if (n < 0) {
            perror("Receive failed");
            continue;
        }

        buf[n] = '\0';

        cout << "Client says: " << buf << endl;

        if (strcmp(buf, "x") == 0) {
            cout << "Server shutting down." << endl;
            break;
        }
    }

    close(sckfd);
    return 0;
}