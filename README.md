# legrep

O legrep é uma ferramenta para pesquisa de padrões de texto, semelhante ao utilitário da linha de comandos grep ( http://en.wikipedia.org/wiki/Grep ). Deverá ter um comportamento igual àquela ferramente quando invocado sem argumentos. Deverá replicar os seguintes argumentos do grep:

    -A num, --after-context=num -> Print num lines of trailing context after each match.  See also the -B and -C options.
    -B num, --before-context=num -> Print num lines of leading context before each match.  See also the -A and -C options.
    -i, --ignore-case -> Perform case insensitive matching.  By default, grep is case sensitive
    -v, --invert-match -> Selected lines are those not matching any of the specified patterns.