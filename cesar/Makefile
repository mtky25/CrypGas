# Makefile para compilar e medir desempenho dos algoritmos blowfish em C e C++
# Parâmetros medidos: tempo, RAM, CPU, throughput

# Caminhos dos arquivos
C_SRC=cesar.c
CPP_SRC=cesar.cpp
C_BIN=cesar
CPP_BIN=cesar_cpp
INPUT=text.txt

# Comando time detalhado
TIME=/usr/bin/time -v


# Regra padrão


# Regra padrão: sempre executa benchmarks, recompilando binários se necessário
all: bench_c bench_cpp bench_py

# Benchmarks dependem dos binários
bench_c: $(C_BIN)
bench_cpp: $(CPP_BIN)
bench_py:

# Benchmarks dependem dos binários
bench_c: $(C_BIN)
bench_cpp: $(CPP_BIN)
bench_py:

# Build C
$(C_BIN): $(C_SRC)
	gcc -O2 -o $(C_BIN) $(C_SRC)

# Build C++
$(CPP_BIN): $(CPP_SRC)
	g++ -O2 -o $(CPP_BIN) $(CPP_SRC) -lcryptopp

PY_SRC=cesar.py
PY_BIN=cesar.py


# Mede desempenho do Python (apenas log final)
bench_py: $(PY_BIN)
	@sz=$$(stat --format="%s" $(INPUT)); \
	start=$$(date +%s.%N); \
	python3 $(PY_BIN) $(INPUT) > /dev/null; \
	end=$$(date +%s.%N); \
	tempo=$$(echo "$$end - $$start" | bc -l); \
	thr=$$(echo "scale=4; ($$sz/$$tempo/1024/1024)" | bc -l); \
	echo "Tempo de execução: $${tempo} segundos" > time_py.log; \
	echo "Tamanho do arquivo: $${sz} bytes" >> time_py.log; \
	echo "Throughput: $${thr} MB/s" >> time_py.log


# Mede desempenho do C (apenas log final)

bench_c: $(C_BIN)
	@sz=$$(stat --format="%s" $(INPUT)); \
	start=$$(date +%s.%N); \
	./$(C_BIN) $(INPUT) > /dev/null; \
	end=$$(date +%s.%N); \
	tempo=$$(echo "$$end - $$start" | bc -l); \
	thr=$$(echo "scale=4; ($$sz/$$tempo/1024/1024)" | bc -l); \
	echo "Tempo de execução: $${tempo} segundos" > time_c.log; \
	echo "Tamanho do arquivo: $${sz} bytes" >> time_c.log; \
	echo "Throughput: $${thr} MB/s" >> time_c.log;


# Mede desempenho do C++ (apenas log final com throughput)
bench_cpp: $(CPP_BIN)
	@sz=$$(stat --format="%s" $(INPUT)); \
	start=$$(date +%s.%N); \
	./$(CPP_BIN) $(INPUT) > /dev/null; \
	end=$$(date +%s.%N); \
	tempo=$$(echo "$$end - $$start" | bc -l); \
	thr=$$(echo "scale=4; ($$sz/$$tempo/1024/1024)" | bc -l); \
	echo "Tempo de execução: $${tempo} segundos" > time_cpp.log; \
	echo "Tamanho do arquivo: $${sz} bytes" >> time_cpp.log; \
	echo "Throughput: $${thr} MB/s" >> time_cpp.log;
