FROM leosocy/opencv:python

LABEL author="leosocy"

# install RobustPalmRoi library
COPY . /tmp/app
RUN apk add --no-cache --virtual build-dependencies make cmake linux-headers git && \
    cd /tmp && git clone https://github.com/jbeder/yaml-cpp.git && \
    cd yaml-cpp && mkdir -p build && cd build && \
    cmake -DBUILD_SHARED_LIBS=ON -DYAML_CPP_BUILD_TESTS=OFF -DYAML_CPP_BUILD_TOOLS=OFF -DYAML_CPP_BUILD_CONTRIB=OFF .. && \
    make install && \
    cd /tmp/app && mkdir build && cd build && \
    cmake .. && make install && \
    cd ../pypackage && python setup.py install && \
    cd / && rm -rf /tmp/* && \
    apk del build-dependencies
