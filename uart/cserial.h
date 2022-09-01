#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#ifndef _CSERIAL_H
#define _CSERIAL_H

#define BACKHOME "199#"
#define LLIGHTON "!11#"
#define LLIGHTOFF "!10#"
#define LAIRON "!21#"
#define LAIROFF "!20#"
#define LAIRHIGH "!22#"
#define LAIRLOW "!23#"
#define LTVON "!31#"
#define LTVOFF "!30#"
#define STARTWORK "299#"
#define STOPWORK "200#"
#define RLIGHTON "@11#"
#define RLIGHTOFF "@10#"
#define RFANON "@21#"
#define RFANOFF "@20#"
#define RFANLIGHTON "@22#"
#define RFANLIGHTOFF "@23#"
#define RFANSWINGSTART "@24#"
#define RFANSWINGSTOP "@25#"
#define GOSLEEP "300#"
#define GETUP "399#"
#define SREADING "&31#"
#define SGOODNIGHT "&30#"
#define GOOUT "400#"

extern int UARTInit (int fd, int speed, int parity);
extern void set_blocking (int fd, int should_block);
extern int UARTOpen(char *name);

#endif
