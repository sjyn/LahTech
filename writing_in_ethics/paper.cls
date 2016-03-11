\ProvidesClass{paper}

\LoadClass[12pt]{article}

\RequirePackage{setspace}
\RequirePackage{luacode}
\RequirePackage{lineno}
\RequirePackage{fontspec}
\RequirePackage[margin=1in]{geometry}
\RequirePackage{hyperref}
\RequirePackage[backend=bibtex,style=mla,showmedium=false]{biblatex}

\date{}
\author{}

\setmainfont{Times New Roman}

\newcommand{\inlinetitle}{\vspace{-1.5cm}{\let\newpage\relax\maketitle}\vspace{-1.5cm}}

\doublespacing

\begin{luacode}
	function printWordCount()
		local exitcode = os.execute("detex ".."\jobname".." | wc -w > count.txt")
		if exitcode == 0 then
			local file = io.open("count.txt")
			if file ~= nil then
				tex.print(""..file:read())
				os.remove("count.txt")
			end
		end
	end
\end{luacode}

\newcommand{\standardhead}{%
	\noindent Group B\\
	\noindent Word Count: \directlua{printWordCount()} \\
	\noindent Meeting Time: MW 1500\\
	\noindent \today
}

\newcommand{\drafth}{%
	\begin{flushright}
		\noindent 5793\\
		\standardhead{}
	\end{flushright}
}

\newcommand{\finalh}{%
	\begin{flushright}
		\noindent Steven Rosendahl 00885793\\
		\standardhead{}
	\end{flushright}
}
