//Javascript Object for douban FM
// Require jQuery library
//
//
var doubanFM = function(){
	this.channelsObj = null;

    this.loadChannels = function(divObject){
       channelsObj = $(divObject);
       var ulChannels = $("<ul></ul>");
       $.ajax({
        url:'http://douban.fm/j/app/radio/channels',
        type:"GET",
        crossDomain:true,
        dataType:"json",
        headers: {
            "Access-Control-Allow-Origin":"http://douban.fm",
            "Access-Control-Allow-Headers":"X-Requested-With"
        }

       }).done(function(data){
        //sucess
        alert("sucess"+data);
       })
       .fail(function(data){
        //error
                alert("error"+data);
       })
       .always(function(data){
        //complete
                alert("complete"+data);
       });
       /*
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
       });*/ //End getJSON
    };
};