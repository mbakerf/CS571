FROM ubuntu

RUN apt-get update -y && apt-get install -y build-essential curl

RUN curl -s 'https://www.student.cs.uwaterloo.ca/~cs350/os161_repository/os161-gcc.tar.gz' | tar -xvz

ADD os161-1.11/ /os161-1.11/

RUN cd os161-1.11/kern/conf && ./config ASST1

#RUN cd os161-1.11/kern/compile/ASST1 && make depend && make && make install

