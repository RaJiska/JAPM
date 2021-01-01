FROM alpine:3.12.3
COPY . /tmp/JAPM
WORKDIR /tmp/JAPM/build
RUN \
	apk add cmake make gcc musl-dev && \
	cmake .. && \
	make

FROM alpine:3.12.3
COPY --from=0 /tmp/JAPM/build/JAPM /usr/bin/JAPM
ENTRYPOINT ["JAPM"]