FROM alpine AS base

WORKDIR /opt

FROM base AS builder

RUN apk update && apk add clang

COPY ./echo.c /opt

RUN clang echo.c -o echo
RUN strip echo

FROM base AS echo-service

COPY --from=builder /opt/echo /opt/

CMD /opt/echo

