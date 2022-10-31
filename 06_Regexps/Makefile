bin:
	gcc esub.c -o esub

test: bin
	./esub '(a).(b)' "\2m\1u\t" 'loshara arb nasd arb shfksdf' > out_util.txt && echo 'loshara arb nasd arb shfksdf' | sed -E 's/(a).(b)/\2m\1u\t/' > out_app.txt && cmp out_util.txt out_app.txt
	rm out*
	./esub 'a(.)b' '\1' 'albania strong' > out_util.txt && echo 'albania strong' | sed -E 's/a(.)b/\1/' > out_app.txt && cmp out_util.txt out_app.txt
	rm out*
	./esub 'l(.).(.)x' '\\2\\1' 'i like linux' > out_util.txt && echo 'i like linux' | sed -E 's/l(.).(.)x/\\2\\1/' > out_app.txt && cmp out_util.txt out_app.txt
	rm out*
	./esub 'l...x' 'windows' 'i like linux' > out_util.txt && echo 'i like linux' | sed -E 's/l...x/windows/' > out_app.txt && cmp out_util.txt out_app.txt

clean:
	rm esub
	rm out*