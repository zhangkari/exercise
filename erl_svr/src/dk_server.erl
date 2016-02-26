%
%
% FileName: dk_server.erl
% Function: dragonkiller server
% Author:   kari.zhang
% Date:	   Mar, 18th, 2014 
%
%


-module(dk_server).

-compile(export_all).
%-export([start/0, start/1]).

-define(TCP_OPTIONS, [binary, {packet, 0}, {active, false}, {reuseaddr, true}]).

start()->
	io:format("start()\n"),
	listen(8899).

%
%
%
start(Port)->
	io:format("start(~w)~n", [Port]),
	listen(Port).


%
% simulate the time
%
timer(Func, Time) %->
	when is_function(Func), is_integer(Time) ->	
		io:format("ok~n"),

	receive
		{cancel, Why} ->
			io:format("Canled ~p ~n", [Why])
	after Time -> 
		io:format("timeout.~n"),
		Func()
	end .

%
% Create server socket
%
listen(Port) ->
	is_integer(Port),
	{ok, LSocket} = gen_tcp:listen(Port, ?TCP_OPTIONS),
	accept(LSocket).


%
% Accept connect from client
%
accept(LSocket) ->
	{ok, Socket} = gen_tcp:accept(LSocket),
	{ok, {IP, PORT}} = inet:peername(Socket),
	io:format("ip:~p, port:~p~n", [IP, PORT]),
	spawn(dk_server, loop_recv, [Socket]),
	accept(LSocket).


%
% Receive connect in loop way
%
loop_recv(Socket) ->
	case gen_tcp:recv(Socket, 0) of
		{ok, Data} ->
			io:format("Data:~p~n", [Data]),
			gen_tcp:send(Socket, Data),
			
			{A, B, C} = now(),
			random:seed(A, B, C),
			Str=io_lib:format("~p", [random:uniform(10000)]),
			gen_tcp:send(Socket, Str),
			gen_tcp:close(Socket),
			loop_recv(Socket);

		{error, closed} ->
			io:format("Cliend closed~n"),
			gen_tcp:close(Socket)
	end.
