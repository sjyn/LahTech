\ProvidesClass{hw}

\LoadClass{article}

\RequirePackage{amsfonts}
\RequirePackage{amsmath}
\RequirePackage{amssymb}
\RequirePackage{graphicx}
\RequirePackage{mathtools}
\RequirePackage{paralist}
\RequirePackage{esvect}

\topmargin=-1in
\textheight=9.2in
\textwidth=168mm
\oddsidemargin=-0.2in
\evensidemargin=-0.2in

\pagenumbering{gobble}

\def\AA{\mathbb{A}}	% Algebraics
\def\CC{\mathbb{C}}	% Complex
\def\FF{\mathbb{F}}	% Arbitrary field
\def\HH{\mathbb{H}}	% Quaternions
\def\KK{\mathbb{K}}	% Arbitrary field
\def\NN{\mathbb{N}}	% Naturals
\def\QQ{\mathbb{Q}}	% Rationals
\def\RR{\mathbb{R}}	% Reals
\def\ZZ{\mathbb{Z}}	% Integers

\newcommand{\twov}[2]{<#1,#2>}
\newcommand{\thrv}[3]{<#1,#2,#3>}
\newcommand{\makeheader}[1]{%
	\noindent\textit{\textbf{Steven Rosendahl\\ Homework #1}}%
}
