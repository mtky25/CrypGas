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

all: $(C_BIN) $(CPP_BIN) bench_c bench_cpp bench_py

PY_SRC=aespy.py

# Mede desempenho do Python
bench_py:
	@echo "\n--- AES Python ---"
	$(TIME) python3 $(PY_SRC) $(INPUT) 2> time_py.log
	@awk '\
		/Elapsed/ { \
			t = $$NF; \
			n = split(t, a, ":"); \
			if (n == 3) tempo = a[1]*3600 + a[2]*60 + a[3]; \
			else if (n == 2) tempo = a[1]*60 + a[2]; \
			else tempo = a[1]; \
		} \
		/Maximum resident set size/ {ram=$$NF} \
		/Percent of CPU/ {cpu=$$NF} \
		END { \
			tempo = tempo + 0.0; \
			printf "\n==== RESULTADO FINAL AES Python ====\n"; \
			printf "Tempo: %.2fs\nRAM: %s KB\nCPU: %s\n", tempo, ram, cpu \
		} \
	' time_py.log >> time_py.log

# Mede desempenho do C
bench_c:
	@echo "\n--- AES C ---"
	$(TIME) ./$(C_BIN) $(INPUT) 2> time_c.log
	@awk '\
		/Elapsed/ { \
			t = $$NF; \
			n = split(t, a, ":"); \
			if (n == 3) tempo = a[1]*3600 + a[2]*60 + a[3]; \
			else if (n == 2) tempo = a[1]*60 + a[2]; \
			else tempo = a[1]; \
		} \
		/Maximum resident set size/ {ram=$$NF} \
		/Percent of CPU/ {cpu=$$NF} \
		END { \
			tempo = tempo + 0.0; \
			printf "\n==== RESULTADO FINAL AES C ====\n"; \
			printf "Tempo: %.2fs\nRAM: %s KB\nCPU: %s\n", tempo, ram, cpu \
		} \
	' time_c.log >> time_c.log

# Mede desempenho do C++
bench_cpp:
	@echo "\n--- AES C++ ---"
	$(TIME) ./$(CPP_BIN) $(INPUT) 2> time_cpp.log
	@awk '\
		/Elapsed/ { \
			t = $$NF; \
			n = split(t, a, ":"); \
			if (n == 3) tempo = a[1]*3600 + a[2]*60 + a[3]; \
			else if (n == 2) tempo = a[1]*60 + a[2]; \
			else tempo = a[1]; \
		} \
		/Maximum resident set size/ {ram=$$NF} \
		/Percent of CPU/ {cpu=$$NF} \
		END { \
			tempo = tempo + 0.0; \
			printf "\n==== RESULTADO FINAL AES C++ ====\n"; \
			printf "Tempo: %.2fs\nRAM: %s KB\nCPU: %s\n", tempo, ram, cpu \
		} \
	' time_cpp.log >> time_cpp.log

# Mede desempenho do C++
bench_cpp:
	@echo "\n--- AES C++ ---"
	$(TIME) ./$(CPP_BIN) $(INPUT) 2> time_cpp.log
	@echo "Tamanho do arquivo de entrada: $$(stat --format=\"%s\" $(INPUT)) bytes" >> time_cpp.log
	@awk '\
		/Elapsed/ { \
			t = $$NF; \
			n = split(t, a, ":"); \
			if (n == 3) tempo = a[1]*3600 + a[2]*60 + a[3]; \
			else if (n == 2) tempo = a[1]*60 + a[2]; \
			else tempo = a[1]; \
		} \
		/Maximum resident set size/ {ram=$$NF} \
		/Percent of CPU/ {cpu=$$NF} \
		/Tamanho do arquivo de entrada:/ {sz=$$NF} \
		END { \
			sub("\"", "", sz); \
			sznum = sz + 0.0; \
			tempo = tempo + 0.0; \
			if (tempo>0) thr=sznum/tempo; else thr=0; \
			printf "\n==== RESULTADO FINAL AES C++ ====\n"; \
			printf "Tempo: %.2fs\nRAM: %s KB\nCPU: %s\nThroughput: %.2f bytes/s\n", tempo, ram, cpu, thr \
		}' time_cpp.log >> time_cpp.log

	@echo "\n--- AES C++ ---"
	$(TIME) ./$(CPP_BIN) $(INPUT) 2> time_cpp.log
	@awk '\
		/Elapsed/ { \
			t = $$NF; \
			n = split(t, a, ":"); \
			if (n == 3) tempo = a[1]*3600 + a[2]*60 + a[3]; \
			else if (n == 2) tempo = a[1]*60 + a[2]; \
			else tempo = a[1]; \
		} \
		/Maximum resident set size/ {ram=$$NF} \
		/Percent of CPU/ {cpu=$$NF} \
		END { \
			tempo = tempo + 0.0; \
			printf "\n==== RESULTADO FINAL AES C++ ====\n"; \
			printf "Tempo: %.2fs\nRAM: %s KB\nCPU: %s\n", tempo, ram, cpu \
		} \
	' time_cpp.log >> time_cpp.log
