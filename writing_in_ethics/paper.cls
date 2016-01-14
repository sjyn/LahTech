\ProvidesClass{paper}
\LoadClass{article}

\RequirePackage{setspace}
\RequirePackage{luacode}

\usepackage{lineno}
\usepackage[margin=1in]{geometry}

\doublespacing
\linenumbers

\begin{luacode}
	function printWordCount()
		local exitcode = os.execute("detex paper_one.tex | wc -w > count.txt")
		if exitcode == 0 then
			local file = io.open("count.txt")
			if file ~= nil then
				tex.print(""..file:read())
			end
		end
	end
\end{luacode}

\newcommand{\standardhead}[1]{%
	\noindent Group B\\
	\noindent Word Count: \directlua{printWordCount()} \\
	\noindent Meeting Time: MW 1500\\
	\noindent \today
}

\newcommand{\drafth}[1]{%
	\begin{flushright}
		\noindent 5793\\
		\standardhead{#1}
	\end{flushright}
}

\newcommand{\finalh}[1]{%
	\begin{flushright}
		\noindent Steven Rosendahl 00885793\\
		\standardhead{#1}
	\end{flushright}
}
