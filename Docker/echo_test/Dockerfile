FROM ubuntu

WORKDIR /opt

RUN apt-get update
RUN apt-get install -y gcc

COPY ./echo.c /opt

RUN gcc echo.c -o echo

CMD /opt/echo

