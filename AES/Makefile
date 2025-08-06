# Makefile para compilar e medir desempenho dos algoritmos AES em C e C++
# Parâmetros medidos: tempo, RAM, CPU, throughput

# Caminhos dos arquivos
C_SRC=aes.c
CPP_SRC=aescpp.cpp
C_BIN=aes
CPP_BIN=aescpp
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

# Build C
$(C_BIN): $(C_SRC)
	gcc -O2 -o $(C_BIN) $(C_SRC)

# Build C++
$(CPP_BIN): $(CPP_SRC)
	g++ -O2 -o $(CPP_BIN) $(CPP_SRC) -lcryptopp

PY_SRC=aespy.py


# Mede desempenho do Python (apenas log final)
bench_py:
	@sz=$$(stat --format="%s" $(INPUT)); \
	$(TIME) python3 $(PY_SRC) $(INPUT) 2> time_py.log; \
	awk -v sz="$$sz" '\
		/Elapsed/ { \
			t = $$NF; \
			n = split(t, a, ":"); \
			if (n == 3) tempo = a[1]*3600 + a[2]*60 + a[3]; \
			else if (n == 2) tempo = a[1]*60 + a[2]; \
			else tempo = a[1]; \
		} \
		END { \
			tempo = tempo + 0.0; \
			thr = (tempo > 0) ? sz/tempo/1024/1024 : 0; \
			printf "Tempo de execução: %.10f segundos\n", tempo; \
			printf "Tamanho do arquivo: %s bytes\n", sz; \
			printf "Throughput: %.4f MB/s\n", thr; \
		} \
	' time_py.log > time_py.log.tmp && mv time_py.log.tmp time_py.log


# Mede desempenho do C (apenas log final)

bench_c: $(C_BIN)
	@sz=$$(stat --format="%s" $(INPUT)); \
	$(TIME) ./$(C_BIN) $(INPUT) 2> time_c.log; \
	awk -v sz="$$sz" '\
		/Elapsed/ { \
			t = $$NF; \
			n = split(t, a, ":"); \
			if (n == 3) tempo = a[1]*3600 + a[2]*60 + a[3]; \
			else if (n == 2) tempo = a[1]*60 + a[2]; \
			else tempo = a[1]; \
		} \
		END { \
			tempo = tempo + 0.0; \
			thr = (tempo > 0) ? sz/tempo/1024/1024 : 0; \
			printf "Tempo de execução: %.10f segundos\n", tempo; \
			printf "Tamanho do arquivo: %s bytes\n", sz; \
			printf "Throughput: %.4f MB/s\n", thr; \
		} \
	' time_c.log > time_c.log.tmp && mv time_c.log.tmp time_c.log


# Mede desempenho do C++ (apenas log final com throughput)
bench_cpp: $(CPP_BIN)
	@sz=$$(stat --format="%s" $(INPUT)); \
	$(TIME) ./$(CPP_BIN) $(INPUT) 2> time_cpp.log; \
	awk -v sz="$$sz" '\
		/Elapsed/ { \
			t = $$NF; \
			n = split(t, a, ":"); \
			if (n == 3) tempo = a[1]*3600 + a[2]*60 + a[3]; \
			else if (n == 2) tempo = a[1]*60 + a[2]; \
			else tempo = a[1]; \
		} \
		END { \
			tempo = tempo + 0.0; \
			thr = (tempo > 0) ? sz/tempo/1024/1024 : 0; \
			printf "Tempo de execução: %.10f segundos\n", tempo; \
			printf "Tamanho do arquivo: %s bytes\n", sz; \
			printf "Throughput: %.4f MB/s\n", thr; \
		} \
	' time_cpp.log > time_cpp.log.tmp && mv time_cpp.log.tmp time_cpp.log
