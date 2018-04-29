.PHONY:all
all:client serve n_serve pthread_serve select poll epoll

client:client.c commn.c
	gcc -o $@ $^
serve:serve.c commn.c
	gcc -o $@ $^
n_serve:n_serve.c commn.c
	gcc -o $@ $^
pthread_serve:pthread_serve.c commn.c
	gcc -o $@ $^ -l pthread
select:select_serve.c commn.c
	gcc -o $@ $^ 
poll:poll_serve.c commn.c
	gcc -o $@ $^ -g 
epoll:epoll_serve.c commn.c
	gcc -o $@ $^ -g 
clean:
	rm -rf serve client n_serve pthread_serve select poll
