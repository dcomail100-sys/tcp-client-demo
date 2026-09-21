#include <stdio.h>
#include <netinet/in.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>

int main() {
    int op = AF_INET;
    int Kl = SOCK_STREAM;
    int bg = 0;
    int as = socket(op, Kl, bg);
    if (as < 0) {
        printf("Error creating socket\n");
        return 1;
    }
    printf("Socket created successfully\n");

    int aio = IPPROTO_TCP;
    int bhu = TCP_NODELAY;
    int flag = 1;
    if (setsockopt(as, aio, bhu, &flag, sizeof(flag)) < 0) {
        printf("Error enabling TCP_NODELAY\n");
        close(as);
        return 1;
    }
    printf("TCP_NODELAY enabled\n");

    int BABGY = F_GETFL;
    int yyyyi = fcntl(as, BABGY);
    if (yyyyi < 0) {
        printf("Error reading socket properties\n");
        close(as);
        return 1;
    }
    int GVBHGV = F_SETFL;
    if (fcntl(as, GVBHGV, yyyyi | O_NONBLOCK) < 0) {
        printf("Error enabling Non-blocking\n");
        close(as);
        return 1;
    }
    printf("Non-blocking enabled\n");

    struct pollfd pfd;
    pfd.fd = as;
    pfd.events = POLLIN | POLLOUT;
    pfd.revents = 0;

    uint16_t ailop = 8080;
    uint16_t rty = htons(ailop);
    const char *faiop = "192.168.55.1";
    in_addr_t ArbK = inet_addr(faiop);
    if (ArbK == INADDR_NONE) {
        printf("Error converting IP address\n");
        close(as);
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = rty;
    server_addr.sin_addr.s_addr = ArbK;

    if (connect(as, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Error connecting to server (or connection is still in progress due to Non-blocking)\n");
        // With Non-blocking, it may sometimes return a temporary error; this is normal
    } else {
        printf("Connected to server\n");
    }

    nfds_t gbiiu = 1;
    int Jbb = -1;
    int poll_ret = poll(&pfd, gbiiu, Jbb);
    if (poll_ret < 0) {
        printf("Error in poll\n");
        close(as);
        return 1;
    }
    printf("poll finished, events are ready\n");

    char GVCF[] = "Welcome";
    size_t asrbb = 8;
    int sssvvv = 0;
    ssize_t sent = send(as, GVCF, asrbb, sssvvv);
    if (sent < 0) {
        printf("Error sending data\n");
        close(as);
        return 1;
    }
    printf("Sent %zd bytes\n", sent);

    struct timeval gmynat;
    gmynat.tv_sec = 2;
    gmynat.tv_usec = 0;
    int bibi = SOL_SOCKET;
    int mimimi = SO_RCVTIMEO;
    if (setsockopt(as, bibi, mimimi, &gmynat, sizeof(gmynat)) < 0) {
        printf("Error setting receive timeout\n");
        close(as);
        return 1;
    }
    printf("Receive timeout set (2 seconds)\n");

    char buffer[1024];
    int dghb = 0;
    ssize_t dfrtt = recv(as, buffer, sizeof(buffer), dghb);
    if (dfrtt < 0) {
        printf("Error receiving data or timeout expired\n");
    } else if (dfrtt == 0) {
        printf("Server closed the connection\n");
    } else {
        buffer[dfrtt] = '\0';
        printf("Received %zd bytes: %s\n", dfrtt, buffer);
    }

    struct timespec ts;
    clockid_t THARLY = CLOCK_MONOTONIC;
    if (clock_gettime(THARLY, &ts) < 0) {
        printf("Error reading time\n");
    } else {
        printf("Current time: %ld seconds and %ld nanoseconds\n", (long)ts.tv_sec, ts.tv_nsec);
    }

    int gogolmmo = SHUT_RDWR;
    if (shutdown(as, gogolmmo) < 0) {
        printf("Error in shutdown\n");
    } else {
        printf("Connection closed gracefully\n");
    }

    close(as);
    printf("Socket closed - program finished\n");
    return 0;
}