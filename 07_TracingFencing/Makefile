GENERATES = wrap.so move

RD='\033[0;31m'
NC='\033[0m' # No Color
GR='\033[0;32m'        # Green

.DEFAULT_GOAL := all

all: wrap.so move

test: test_read_fault test_write_fault test_openat_fault test_PROTECTED test_UNPROTECTED test_openat1_fault

wrap.so: unlink_wrapper.c
	cc -shared -fPIC unlink_wrapper.c -o $@ -ldl

move: move.c
	cc move.c -O0 -o $@

run: move
	./move input_PROTECT output_text

run_wrapped: move wrap.so
	LD_PRELOAD=./wrap.so ./move input_PROTECT output_text

# I check for 0 return code so every fault is "catched"

# Check for reading data from input file
test_read_fault: 
	touch file.txt && echo "sdlfslkjdfjkdsgdsfg" > file.txt
	LD_PRELOAD=./wrap.so strace -e trace=read -e fault=read:when=4:error=EIO ./move file.txt res0.txt
	if [ $$? -ne 0 ]; then echo -e "${RD}ERROR in READ fault processing ${NC}"; fi
	if [ -f  file.txt ] ; then echo -e "${GR} PASS ${NC}" ; else echo "${RD} ERROR in READ fault processing ${NC}"; fi
	rm file.txt

# Check for writing data to output file
test_write_fault:
	touch file.txt && echo "sdlfslkjdfjkdsgdsfg" > file.txt
	LD_PRELOAD=./wrap.so strace -e trace=write -e fault=write:when=1:error=EINTR ./move file.txt res0.txt
	if [ $$? -ne 0 ]; then echo -e "${RD}ERROR in READ fault processing ${NC}"; fi
	if [ -f  file.txt ] ; then echo -e "${GR} PASS ${NC}" ; else echo "${RD} ERROR in READ fault processing ${NC}"; fi
	rm file.txt

# Check for input file error opening
test_openat_fault:
	touch file.txt && echo "sdlfslkjdfjkdsgdsfg" > file.txt
	LD_PRELOAD=./wrap.so strace -e trace=openat -e fault=openat:when=5:error=ENOENT ./move file.txt res0.txt
	if [ $$? -ne 0 ]; then echo -e "${RD}ERROR in READ fault processing ${NC}"; fi
	if [ -f  file.txt ] ; then echo -e "${GR} PASS ${NC}" ; else echo "${RD} ERROR in READ fault processing ${NC}"; fi
	rm file.txt

# Check for output file error opening
test_openat1_fault:
	touch file.txt && echo "sdlfslkjdfjkdsgdsfg" > file.txt
	LD_PRELOAD=./wrap.so strace -e trace=openat -e fault=openat:when=6:error=ENOENT ./move file.txt res0.txt
	if [ $$? -ne 0 ]; then echo -e "${RD}ERROR in READ fault processing ${NC}"; fi
	if [ -f  file.txt ] ; then echo -e "${GR} PASS ${NC}" ; else echo "${RD} ERROR in READ fault processing ${NC}"; fi
	rm file.txt


test_PROTECTED: move wrap.so
	touch filePROTECT.txt && echo "sdlfslkjdfjkdsgdsfg" > filePROTECT.txt
	LD_PRELOAD=./wrap.so ./move filePROTECT.txt output.txt
	if [ -f  filePROTECT.txt ] ; then echo -e "${GR} PASS ${NC}" ; else echo "${RD} ERROR in PROTECTED test ${NC}"; fi

test_UNPROTECTED: move wrap.so
	touch file.txt && echo "sdlfslkjdfjkdsgdsfg" > file.txt
	LD_PRELOAD=./wrap.so ./move file.txt output.txt
	if [ -f  file.txt ] ; then echo -e "${RD} ERROR in UNPROTECTED test ${NC}" ; else echo "${GR} PASS ${NC}"; fi

clean:
	rm $(GENERATES)