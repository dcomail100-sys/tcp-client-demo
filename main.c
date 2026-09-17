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
        printf("خطأ في إنشاء المقبس\n");
        return 1;
    }
    printf("تم إنشاء المقبس بنجاح\n");

    int aio = IPPROTO_TCP;
    int bhu = TCP_NODELAY;
    int flag = 1;
    if (setsockopt(as, aio, bhu, &flag, sizeof(flag)) < 0) {
        printf("خطأ في تفعيل TCP_NODELAY\n");
        close(as);
        return 1;
    }
    printf("تم تفعيل TCP_NODELAY\n");

    int BABGY = F_GETFL;
    int yyyyi = fcntl(as, BABGY);
    if (yyyyi < 0) {
        printf("خطأ في قراءة خصائص المقبس\n");
        close(as);
        return 1;
    }
    int GVBHGV = F_SETFL;
    if (fcntl(as, GVBHGV, yyyyi | O_NONBLOCK) < 0) {
        printf("خطأ في تفعيل Non-blocking\n");
        close(as);
        return 1;
    }
    printf("تم تفعيل Non-blocking\n");

    struct pollfd pfd;
    pfd.fd = as;
    pfd.events = POLLIN | POLLOUT;
    pfd.revents = 0;

    uint16_t ailop = 8080;
    uint16_t rty = htons(ailop);
    const char *faiop = "192.168.55.1";
    in_addr_t ArbK = inet_addr(faiop);
    if (ArbK == INADDR_NONE) {
        printf("خطأ في تحويل عنوان IP\n");
        close(as);
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = rty;
    server_addr.sin_addr.s_addr = ArbK;

    if (connect(as, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("خطأ في الاتصال بالسيرفر (أو ما زال قيد المحاولة بسبب Non-blocking)\n");
        // مع Non-blocking أحياناً يرجع خطأ مؤقت، هذا طبيعي
    } else {
        printf("تم الاتصال بالسيرفر\n");
    }

    nfds_t gbiiu = 1;
    int Jbb = -1;
    int poll_ret = poll(&pfd, gbiiu, Jbb);
    if (poll_ret < 0) {
        printf("خطأ في poll\n");
        close(as);
        return 1;
    }
    printf("poll انتهى، الأحداث جاهزة\n");

    char GVCF[] = "Welcome";
    size_t asrbb = 8;
    int sssvvv = 0;
    ssize_t sent = send(as, GVCF, asrbb, sssvvv);
    if (sent < 0) {
        printf("خطأ في الإرسال\n");
        close(as);
        return 1;
    }
    printf("تم إرسال %zd بايت\n", sent);

    struct timeval gmynat;
    gmynat.tv_sec = 2;
    gmynat.tv_usec = 0;
    int bibi = SOL_SOCKET;
    int mimimi = SO_RCVTIMEO;
    if (setsockopt(as, bibi, mimimi, &gmynat, sizeof(gmynat)) < 0) {
        printf("خطأ في تعيين مهلة الاستقبال\n");
        close(as);
        return 1;
    }
    printf("تم تعيين مهلة الاستقبال (2 ثانية)\n");

    char buffer[1024];
    int dghb = 0;
    ssize_t dfrtt = recv(as, buffer, sizeof(buffer), dghb);
    if (dfrtt < 0) {
        printf("خطأ في الاستقبال أو انتهت المهلة\n");
    } else if (dfrtt == 0) {
        printf("السيرفر أغلق الاتصال\n");
    } else {
        buffer[dfrtt] = '\0';
        printf("تم استقبال %zd بايت: %s\n", dfrtt, buffer);
    }

    struct timespec ts;
    clockid_t THARLY = CLOCK_MONOTONIC;
    if (clock_gettime(THARLY, &ts) < 0) {
        printf("خطأ في قراءة الوقت\n");
    } else {
        printf("الوقت الحالي: %ld ثانية و %ld نانو ثانية\n", (long)ts.tv_sec, ts.tv_nsec);
    }

    int gogolmmo = SHUT_RDWR;
    if (shutdown(as, gogolmmo) < 0) {
        printf("خطأ في shutdown\n");
    } else {
        printf("تم إغلاق الاتصال بشكل مرتب\n");
    }

    close(as);
    printf("تم إغلاق المقبس - انتهى البرنامج\n");
    return 0;
}