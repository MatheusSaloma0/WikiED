# WikiED
Trabalho de Estrutura de Dados 

Professora Patrícia	Dockhorn Costa

Na última	década,	um grande	número de	sistemas colaborativos apareceram	na Web. Exemplos	
clássicos	são	a	Wikipedia,Linux	e	Yahoo! Answers. Nestes sistemas, usuários finais colaboram
para construir algum artefato que será útil para toda	a comunidade.	No caso	da Wikipedia,	em 
particular,	seus usuários	finais são responsáveis por	editar colaborativamente as	páginas da 
enciclopédia.Muitas pessoas colaboram diariamente e milhares	de páginas são editadas	por	hora. 
Todas	as mudanças	são	armazenadas em históricos, o que permite a visualização	dos	editores e das	
modificações feitas nas páginas.

Neste	trabalho é implementado	um sistema que simula a construção colaborativa	de uma enciclopédia	
similar	à	Wikipedia, chamada de WikED!. Chamaremos de	“Página” os	artigos	que	serão	editados 
colaborativamente	pelos usuários, que	exercem, neste contexto, o papel de	“Editores”.	As páginas	 
serão	construídas	a	partir de	“Colaborações”,	ou seja, pedaços de texto	fornecidos pelos editores.	 
Portanto,	editores poderão contribuir com	colaborações para	diferentes páginas. Além de	colaborações,
páginas também podem possuir “Links” para outras página. É	mantido o histórico	de colaborações e	links,
para que tenhamos um panorama, a	qualquer instante, dos editores	e das	modificações das páginas.

Impressão de uma página WikiED!:

Quando for pedido	para imprimir	uma	determinada	página (será fornecido o nome do arquivo),	
deve-se	abrir	o	arquivo	e	incluir	as	seguintes	informações:	
Página	<nome da pagina>

Histórico	de	Contribuições: Lista de contribuções (nomes dos	arquivos), com os nomes dos	
respectivos editores responsáveis. Caso a contribuição tenha sido	retirada pelo	editor, deve-se	
informar que a contribuição foi retirada por seu respectivo editor.

Lista de Links: links para outras páginas.

Textos: Trechos	de texto fornecidos	pelos	editores, na ordem com que foram incluídos (as	
contribuições	retiradas	não	devem	ser	consideradas).

Como saídas do trabalho, além dos arquivos com as páginas da WikED!, será gerado um arquivo de	
“log” para possíveis mensagens de erro e para informar se há caminho entre duas	páginas	(por meio	de links).	
