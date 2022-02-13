#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

void SetUp(struct termios *tty);

int main(){
    FILE *fp;
    fp = fopen("UserLogin.txt","w");
    int serial_port = open("/dev/ttyUSB0", O_RDWR);
    if(serial_port < 0)
        printf("Error %i\n", errno);
    
        //Configuring termios
    struct termios tty, *t;
    t = &tty;

    if(tcgetattr(serial_port,&tty)!=0)
        printf("Error %i\n", errno);

    void SetUp(struct termios *tty);
    
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0)
        printf("Error %i\n", errno);    

    char read_buf[3];
        while(1){
        int n = read(serial_port, &read_buf, sizeof(read_buf));
        if(n!=0){
            if(read_buf[0]=='1'){
                printf("David Poljvas, Welcome\n");
                system("xdg-open https://www.youtube.com/watch?v=l482T0yNkeo");
            }
            else 
                printf("Unathorized user!\n");
        }
      }
      close(serial_port);
      fclose(fp);
      return 0;
}

void SetUp(struct termios *tty){

    tty->c_cflag &= ~PARENB;// Clear parity bit, disabling parity (most common)
    tty->c_cflag &= ~CSTOPB;// Clear stop field, only one stop bit used in communication (most common)
    tty->c_cflag &= ~CSIZE;// Clear all the size bits, then use one of the statements below
    tty->c_cflag |= CS8;// 8 bits per byte (most common)
    tty->c_cflag &= ~CRTSCTS;// Disable RTS/CTS hardware flow control (most common)
    tty->c_cflag |= CREAD | CLOCAL;// Turn on READ & ignore ctrl lines (CLOCAL = 1)
    tty->c_lflag &= ~ICANON;//canonical or non-canonical mode (canonical libe-by-line)
    tty->c_lflag &= ~ECHO;//Disable echo
    tty->c_lflag &= ~ECHOE;//Disable erauser
    tty->c_lflag &= ~ECHONL;//Disable new-line echo
    tty->c_lflag &= ~ISIG;// Disable interpretation of INTR, QUIT and SUSP
    tty->c_iflag &= ~(IXON | IXOFF | IXANY);// Turn off s/w flow ctrl
    tty->c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);// Disable any special handling of received bytes
    tty->c_oflag &= ~OPOST;// Prevent special interpretation of output bytes (e.g. newline chars)
    tty->c_oflag &= ~ONLCR;// Prevent conversion of newline to carriage return/line feed

    tty->c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty->c_cc[VMIN] = 0;

    cfsetispeed(tty,B9600);//input Baud rate
    cfsetospeed(tty,B9600);//output Baud rate
}
