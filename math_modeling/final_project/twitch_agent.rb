#!/usr/bin/env ruby

require 'twitch'
require 'pp'
require 'json'
require 'net/http'

require './const.rb'

def main
    twitch = Twitch.new({
        client_id: Const.cid,
        secret_key: Const.secret_key,
        redirect_uri: "http://localhost",
        scope: ["user_read"]
    })

    twitch.link

    user = twitch.channel 'capcomfighters'
    userhash = Net::HTTP.get(URI(user[:body].parsed_response["_links"]['chat']))
    userself = JSON.parse(userhash)['_links']
    pp userself
end

main
