//Javascript Object for douban FM
// Require jQuery library
//
//
var doubanFM = function(){
	this.channelsObj = null;

    this.loadChannels = function(divObject){
       channelsObj = $(divObject);
       var ulChannels = $("<ul></ul>");
       $.getJSON("http://douban.fm/j/app/radio/channels",function(data){
       	  for (var i = 0; i < data.channels.length; i++) {
       	  	var liChannel = $("<li></li>");
       	  	var butChannel = $("<a channelId='"+data.channels[i].channel_id+"' >" + data.channels[i].name + "</a>");
       	  	butChannel.bind("click",function(){
       	  		alert($(this).attr("channelId"));
       	  	});
       	  	liChannel.append(butChannel);
       	  	ulChannels.append(liChannel);
       	  };
       	  channelsObj.append(ulChannels);
       });
    };
};