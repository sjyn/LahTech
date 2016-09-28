max(0,[]).
max(X,[X]).
max(A,[H|T]) :-
    max(M,T),
    ((H>M,A is H);
    (H=<M,A is M)).

flexCDR(B,N,B):-
    N < 0;
    N = 0.
flexCDR([],_,[]).
flexCDR(A,N,[_|T]) :-
    N > 0,
    N1 is N - 1,
    flexCDR(A,N1,T).

car([],[]).
car(H,[H,_]).
frontCAR(0,[]).
frontCAR(1,[H|T]) :-
    car(X,T),
    X \= H.
frontCAR(L,[H|T]) :-
    append(Prefix, Suffix, [H|T]),
    [H1|_] = Prefix,
    [H2|_] = Suffix,
	H1 \= H2,
    length(Prefix,L),
    list_to_set(Prefix,Set),
    length(Set,1).
