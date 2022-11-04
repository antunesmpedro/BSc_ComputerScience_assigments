% Subset da linguaguem "dado" no enunciado
% È frase se for: frase nominal, frase nominal + frase verbal(singular e plural).
sentence(sentence(FN)) --> frase_nom(FN).
sentence(sentence(FN,FV)) --> frase_nom(FN), frase_verb(FV).
sentence(sentence(FN,FV)) --> frase_nom_p(FN), frase_verb_p(FV).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Frase Nominal
frase_nom(frase_nom(A,S)) --> artigo_f(A), subst_f(S).
frase_nom(frase_nom(A,S)) --> artigo_m(A), subst_m(S).
frase_nom(frase_nom(S)) --> subst_f(S).
frase_nom(frase_nom(S)) --> subst_m(S).

artigo_f(artigo('A')) --> ['A'].
artigo_m(artigo('O')) --> ['O'].

subst_f(substantivo(menina)) --> [menina].
subst_f(substantivo(floresta)) --> [floresta].
subst_f(substantivo(vida)) --> [vida].
subst_f(substantivo(mae)) --> [mae].
subst_f(substantivo(noticia)) --> [noticia].
subst_f(substantivo(porta)) --> [porta].
subst_f(substantivo(cidade)) --> [cidade].

subst_m(substantivo(tempo)) --> [tempo].
subst_m(substantivo(cacador)) --> [cacador].
subst_m(substantivo(rio)) --> [rio].
subst_m(substantivo(mar)) --> [mar].
subst_m(substantivo(vento)) --> [vento].
subst_m(substantivo(martelo)) --> [martelo].
subst_m(substantivo(cachorro)) --> [cachorro].
subst_m(substantivo(tambor)) --> [tambor].
subst_m(substantivo(sino)) --> [sino].
subst_m(substantivo(rosto)) --> [rosto].

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Frase Verbal
frase_verb(frase_verb(V,FN)) --> verb(V), frase_nom(FN).
frase_verb(frase_verb(V)) --> verb(V).
frase_verb(frase_verb(V,FF)) --> verb(V), frase_nom_cont(FF).
frase_verb(frase_verb(V,FP)) --> verb(V), frase_com_prep(FP).

verb(verbo(correu)) --> [correu].
verb(verbo(corre)) --> [corre].
verb(verbo(bateu)) --> [bateu].

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Frase Nominal Plural
frase_nom_p(frase_nom(A,S)) --> artigo_p_f(A), subst_p_f(S).
frase_nom_p(frase_nom(A,S)) --> artigo_p_m(A), subst_p_m(S).
frase_nom_p(frase_nom(S)) --> subst_p_f(S).
frase_nom_p(frase_nom(S)) --> subst_p_m(S).


artigo_p_f(artigo('As')) --> ['As'].
artigo_p_m(artigo('Os')) --> ['Os'].

subst_p_f(substantivo(lagrimas)) --> [lagrimas].
subst_p_f(substantivo(meninas)) --> [meninas].

subst_p_m(substantivo(tambores)) --> [tambores].
subst_p_m(substantivo(lobos)) --> [lobos].


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%frase Verbal Plural
frase_verb_p(frase_verb(V,FN)) --> verb_p(V), frase_nom(FN).
frase_verb_p(frase_verb(V)) --> verb_p(V).
frase_verb_p(frase_verb(V,FF)) --> verb_p(V), frase_nom_cont(FF).
frase_verb_p(frase_verb(V,FP)) --> verb_p(V), frase_com_prep(FP).

verb_p(verbo(corriam)) --> [corriam].
verb_p(verbo(bateram)) --> [bateram].

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Frase Nominal com Contrações
frase_nom_cont(frase_nom(F,S)) --> cont_m(F), subst_m(S).
frase_nom_cont(frase_nom(F,S)) --> cont_f(F), subst_f(S).

cont_f(artigo(na)) --> [na].
cont_f(artigo(pela)) --> [pela].

cont_m(artigo(no)) --> [no].
cont_m(artigo(pelo)) --> [pelo].

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Frase verbal com Preposições
frase_com_prep(frase_com_prep(P,FN)) --> prep(P), frase_nom_c(FN).

prep(preposicao(para)) --> [para].
prep(preposicao(com)) --> [com].

%frase nominal composta
% No caso de ter uma frase nominal com preposição + nominal
frase_nom_c(frase_nom(A,S)) --> artigo_f(A), subst_f(S).
frase_nom_c(frase_nom(A,S)) --> artigo_m(A), subst_m(S).
frase_nom_c(frase_nom(A,S)) --> artigo_p_f(A), subst_p_f(S).
frase_nom_c(frase_nom(A,S)) --> artigo_p_m(A), subst_p_m(S).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%