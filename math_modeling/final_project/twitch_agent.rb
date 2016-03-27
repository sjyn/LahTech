#!/usr/bin/env ruby

require 'rubygems'
require 'twitch'
require 'pp'
require 'json'
# require 'twitch-chat'
# require 'nokogiri'
require 'open-uri'
require 'open_uri_redirections'
require 'thread_safe'
# require 'cinch'

require './const.rb'

$avail = [
    'TriHex',
    'Calebhart42',
    'pearstrike',
    'GameJo6',
    'carcinogen_sda',
    'Fuzzyness',
    'Kungfufruitcup',
    'BubblesDelFuego',
    'Geoff',
    'Sk84uhlivin',
    'callofduty'
]

$users = ThreadSafe::Hash.new

def main
    twitch = Twitch.new({
        client_id: Const.cid,
        secret_key: Const.secret_key,
        redirect_uri: "http://localhost",
        scope: ["user_read"]
    })
    twitch.link

    while true
        i = 0
        threads = []
        $avail.each do |streamer|
            initUser = twitch.stream streamer
            isOnline = (initUser[:body].parsed_response["stream"] != nil)
            if isOnline
                puts "#{streamer} is online; infecting their streamers"
                $users[streamer] = "infected"
                threads[i] = Thread.new {
                    raw = open("https://tmi.twitch.tv/group/user/#{streamer}/chatters",
                        :allow_redirections => :safe)
                    contents = raw.read
                    hashed = JSON.parse contents
                    viewers = hashed["chatters"]["viewers"]
                    viewers.each do |viewer|
                        $users[viewer] = "infected"
                    end
                }
            else
                puts "#{streamer} is offline"
            end
        end

        threads.each do |tr|
            tr.join
        end

        puts 'infected all watchers'

        fdes = File.open('rblog.txt', 'a')
        fdes.puts "Num Infected: #{$users.size}"
        fdes.close

        $users.each do |key, val|
            $avail.push(key)
        end
        sleep(60)
    end


end

main
