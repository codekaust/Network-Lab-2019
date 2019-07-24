#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <iostream>
#include <string.h>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    struct ifreq ifr;
    int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    string result;
    char buffer[3];
    strcpy(ifr.ifr_name, "enp3s0");

    if (ioctl(fd, SIOCGIFHWADDR, &ifr) == 0) {
        for (int i = 0; i <= 5; i++){
            snprintf(buffer, sizeof(buffer), "%.2x", (unsigned char)ifr.ifr_addr.sa_data[i]);
            result = (result + buffer + ":");
        }
        cout << "MAC address of this computer is: " << result << endl;
        return 0;
    }

    return 1;
}