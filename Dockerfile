FROM gcc:10
WORKDIR /app/
COPY ./* ./
RUN g++ opg2.cpp -o opg
RUN chmod +x opg