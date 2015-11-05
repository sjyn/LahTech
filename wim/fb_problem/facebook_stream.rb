require_relative "const.rb"
require "facebook_oauth"

def routine
	client = FacebookOauth::Client.new(
		:application_id => Constants.oh_one,
		:application_secret => Constants.oh_two,
		:callback => Constants.oh_three
	)
	client.authorize_url => 
		"https://graph.facebook.com/oauth/authorize?scope=SCOPE&client_id=ID&type=web_server&redirect_uri=CALLBACK"
		
end