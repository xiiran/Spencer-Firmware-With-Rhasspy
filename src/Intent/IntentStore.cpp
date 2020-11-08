#include "IntentStore.h"
#include "TimeIntent.h"
#include "JokeIntent.h"
#include "StopwatchIntent.h"
#include "../Services/TimeService/TimeService.h"
#include "Funpack/Name.hpp"

std::map<const char*, IntentInfo, IntentStore::CStrCompare> IntentStore::storage;

void IntentStore::fillStorage(){
	storage["time"] = {
			"time",
			[](const std::map<std::string, std::string>& params) -> Intent*{
				TimeIntentParam launchParams {TimeIntentType::TIME, TimeService.getTime()};
				return new TimeIntent(&launchParams);
			},
			nullptr
	};

	storage["joke"] = {
			"joke",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new JokeIntent(); },
			nullptr
	};

	storage["stopwatch"] = {
			"stopwatch",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new StopwatchIntent(); },
			nullptr
	};

	storage["funpack.name"] = {
		"funpack.name",
		[](const std::map<std::string, std::string>&) -> Intentname{ return new FunpackName(); },
		nullptr
	};
	storage["funpack.feeling"] = {
			"funpack.feeling",
			[](const std::map<std::string, std::string>&) -> Intentfeeling{ return new FunpackFeeling(); },
			nullptr
	};
	storage["funpack.whatcanyoudo"] = {
			"funpack.whatcanyoudo",
			[](const std::map<std::string, std::string>&) -> Intentwhatcanyoudo{ return new FunpackWhatcanyoudo(); },
			nullptr
	};
	storage["funpack.help"] = {
			"funpack.help",
			[](const std::map<std::string, std::string>&) -> Intenthelp{ return new FunpackHelp(); },
			nullptr
	};
	storage["funpack.hello"] = {
			"funpack.hello",
			[](const std::map<std::string, std::string>&) -> Intenthello{ return new FunpackHello(); },
			nullptr
	};
	storage["funpack.horoscope"] = {
			"funpack.horoscope",
			[](const std::map<std::string, std::string>&) -> Intenthoroscope{ return new FunpackHoroscope(); },
			nullptr
	};
	storage["funpack.age"] = {
			"funpack.age",
			[](const std::map<std::string, std::string>&) -> Intentage{ return new FunpackAge(); },
			nullptr
	};
	storage["funpack.girlfriend"] = {
			"funpack.girlfriend",
			[](const std::map<std::string, std::string>&) -> Intentgirlfriend{ return new FunpackGirlfriend(); },
			nullptr
	};
	storage["funpack.boyfriend"] = {
			"funpack.boyfriend",
			[](const std::map<std::string, std::string>&) -> Intentboyfriend{ return new FunpackBoyfriend(); },
			nullptr
	};
	storage["funpack.color"] = {
			"funpack.color",
			[](const std::map<std::string, std::string>&) -> Intentcolor{ return new FunpackColor(); },
			nullptr
	};
	storage["funpack.siblings"] = {
			"funpack.siblings",
			[](const std::map<std::string, std::string>&) -> Intentsiblings{ return new FunpackSiblings(); },
			nullptr
	};
	storage["funpack.creator"] = {
			"funpack.creator",
			[](const std::map<std::string, std::string>&) -> Intentcreator{ return new FunpackCreator(); },
			nullptr
	};
	storage["funpack.meaningoflife"] = {
			"funpack.meaningoflife",
			[](const std::map<std::string, std::string>&) -> Intentmeaningoflife{ return new FunpackMeaningoflife(); },
			nullptr
	};
	storage["funpack.wheredoyoucomefrom"] = {
			"funpack.wheredoyoucomefrom",
			[](const std::map<std::string, std::string>&) -> Intentwheredoyoucomefrom{ return new FunpackWheredoyoucomefrom(); },
			nullptr
	};
	storage["funpack.language"] = {
			"funpack.language",
			[](const std::map<std::string, std::string>&) -> Intentlanguage{ return new FunpackLanguage(); },
			nullptr
	};
	storage["funpack.alexa"] = {
			"funpack.alexa",
			[](const std::map<std::string, std::string>&) -> Intentalexa{ return new FunpackAlexa(); },
			nullptr
	};
	storage["funpack.siri"] = {
			"funpack.siri",
			[](const std::map<std::string, std::string>&) -> Intentsiri{ return new FunpackSiri(); },
			nullptr
	};
	storage["funpack.cortana"] = {
			"funpack.cortana",
			[](const std::map<std::string, std::string>&) -> Intentcortana{ return new FunpackCortana(); },
			nullptr
	};
	storage["funpack.google"] = {
			"funpack.google",
			[](const std::map<std::string, std::string>&) -> Intentgoogle{ return new FunpackGoogle(); },
			nullptr
	};
	storage["funpack.bigsby"] = {
			"funpack.bigsby",
			[](const std::map<std::string, std::string>&) -> Intentbigsby{ return new FunpackBigsby(); },
			nullptr
	};
	storage["funpack.freetime"] = {
			"funpack.freetime",
			[](const std::map<std::string, std::string>&) -> Intentfreetime{ return new FunpackFreetime(); },
			nullptr
	};
	storage["funpack.whatsup"] = {
			"funpack.whatsup",
			[](const std::map<std::string, std::string>&) -> Intentwhatsup{ return new FunpackWhatsup(); },
			nullptr
	};
	storage["funpack.married"] = {
			"funpack.married",
			[](const std::map<std::string, std::string>&) -> Intentmarried{ return new FunpackMarried(); },
			nullptr
	};
	storage["funpack.beyourboyfriend"] = {
			"funpack.beyourboyfriend",
			[](const std::map<std::string, std::string>&) -> Intentbeyourboyfriend{ return new FunpackBeyourboyfriend(); },
			nullptr
	};
	storage["funpack.changename"] = {
			"funpack.changename",
			[](const std::map<std::string, std::string>&) -> Intentchangename{ return new FunpackChangename(); },
			nullptr
	};
	storage["funpack.calldifferently"] = {
			"funpack.calldifferently",
			[](const std::map<std::string, std::string>&) -> Intentcalldifferently{ return new FunpackCalldifferently(); },
			nullptr
	};
	storage["funpack.piratetalk"] = {
			"funpack.piratetalk",
			[](const std::map<std::string, std::string>&) -> Intentpiratetalk{ return new FunpackPiratetalk(); },
			nullptr
	};
	storage["funpack.whatdoyoudo"] = {
			"funpack.whatdoyoudo",
			[](const std::map<std::string, std::string>&) -> Intentwhatdoyoudo{ return new FunpackWhatdoyoudo(); },
			nullptr
	};
	storage["funpack.howdidyoulearnenglish"] = {
			"funpack.howdidyoulearnenglish",
			[](const std::map<std::string, std::string>&) -> Intenthowdidyoulearnenglish{ return new FunpackHowdidyoulearnenglish(); },
			nullptr
	};
	storage["funpack.whoispresident"] = {
			"funpack.whoispresident",
			[](const std::map<std::string, std::string>&) -> Intentwhoispresident{ return new FunpackWhoispresident(); },
			nullptr
	};
	storage["funpack.howwasyourday"] = {
			"funpack.howwasyourday",
			[](const std::map<std::string, std::string>&) -> Intenthowwasyourday{ return new FunpackHowwasyourday(); },
			nullptr
	};
	storage["funpack.offense"] = {
			"funpack.offense",
			[](const std::map<std::string, std::string>&) -> Intentoffense{ return new FunpackOffense(); },
			nullptr
	};
	storage["funpack.favouritemovie"] = {
			"funpack.favouritemovie",
			[](const std::map<std::string, std::string>&) -> Intentfavouritemovie{ return new FunpackFavouritemovie(); },
			nullptr
	};
	storage["funpack.newonnetflix"] = {
			"funpack.newonnetflix",
			[](const std::map<std::string, std::string>&) -> Intentnewonnetflix{ return new FunpackNewonnetflix(); },
			nullptr
	};
	storage["funpack.areyouok"] = {
			"funpack.areyouok",
			[](const std::map<std::string, std::string>&) -> Intentareyouok{ return new FunpackAreyouok(); },
			nullptr
	};
	storage["funpack.findrecipe"] = {
			"funpack.findrecipe",
			[](const std::map<std::string, std::string>&) -> Intentfindrecipe{ return new FunpackFindrecipe(); },
			nullptr
	};
	storage["funpack.findphone"] = {
			"funpack.findphone",
			[](const std::map<std::string, std::string>&) -> Intentfindphone{ return new FunpackFindphone(); },
			nullptr
	};
	storage["funpack.longtimenosee"] = {
			"funpack.longtimenosee",
			[](const std::map<std::string, std::string>&) -> Intentlongtimenosee{ return new FunpackLongtimenosee(); },
			nullptr
	};
	storage["funpack.tellstory"] = {
			"funpack.tellstory",
			[](const std::map<std::string, std::string>&) -> Intenttellstory{ return new FunpackTellstory(); },
			nullptr
	};
	storage["funpack.whatsoundfiretruck"] = {
			"funpack.whatsoundfiretruck",
			[](const std::map<std::string, std::string>&) -> Intentwhatsoundfiretruck{ return new FunpackWhatsoundfiretruck(); },
			nullptr
	};
	storage["funpack.catsounds"] = {
			"funpack.catsounds",
			[](const std::map<std::string, std::string>&) -> Intentcatsounds{ return new FunpackCatsounds(); },
			nullptr
	};
	storage["funpack.dogsound"] = {
			"funpack.dogsound",
			[](const std::map<std::string, std::string>&) -> Intentdogsound{ return new FunpackDogsound(); },
			nullptr
	};
	storage["funpack.horsesound"] = {
			"funpack.horsesound",
			[](const std::map<std::string, std::string>&) -> Intenthorsesound{ return new FunpackHorsesound(); },
			nullptr
	};
	storage["funpack.goatsheepsound"] = {
			"funpack.goatsheepsound",
			[](const std::map<std::string, std::string>&) -> Intentgoatsheepsound{ return new FunpackGoatsheepsound(); },
			nullptr
	};
	storage["funpack.pigsound"] = {
			"funpack.pigsound",
			[](const std::map<std::string, std::string>&) -> Intentpigsound{ return new FunpackPigsound(); },
			nullptr
	};
	storage["funpack.cowsound"] = {
			"funpack.cowsound",
			[](const std::map<std::string, std::string>&) -> Intentcowsound{ return new FunpackCowsound(); },
			nullptr
	};
	storage["funpack.donkeysound"] = {
			"funpack.donkeysound",
			[](const std::map<std::string, std::string>&) -> Intentdonkeysound{ return new FunpackDonkeysound(); },
			nullptr
	};
	storage["funpack.chikensound"] = {
			"funpack.chikensound",
			[](const std::map<std::string, std::string>&) -> Intentchikensound{ return new FunpackChikensound(); },
			nullptr
	};
	storage["funpack.roostersound"] = {
			"funpack.roostersound",
			[](const std::map<std::string, std::string>&) -> Intentroostersound{ return new FunpackRoostersound(); },
			nullptr
	};
	storage["funpack.birdsound"] = {
			"funpack.birdsound",
			[](const std::map<std::string, std::string>&) -> Intentbirdsound{ return new FunpackBirdsound(); },
			nullptr
	};
	storage["funpack.owlsound"] = {
			"funpack.owlsound",
			[](const std::map<std::string, std::string>&) -> Intentowlsound{ return new FunpackOwlsound(); },
			nullptr
	};
	storage["funpack.duckgeesesound"] = {
			"funpack.duckgeesesound",
			[](const std::map<std::string, std::string>&) -> Intentduckgeesesound{ return new FunpackDuckgeesesound(); },
			nullptr
	};
	storage["funpack.turkeysound"] = {
			"funpack.turkeysound",
			[](const std::map<std::string, std::string>&) -> Intentturkeysound{ return new FunpackTurkeysound(); },
			nullptr
	};
	storage["funpack.mosquitosound"] = {
			"funpack.mosquitosound",
			[](const std::map<std::string, std::string>&) -> Intentmosquitosound{ return new FunpackMosquitosound(); },
			nullptr
	};
	storage["funpack.cricketsound"] = {
			"funpack.cricketsound",
			[](const std::map<std::string, std::string>&) -> Intentcricketsound{ return new FunpackCricketsound(); },
			nullptr
	};
	storage["funpack.frogsound"] = {
			"funpack.frogsound",
			[](const std::map<std::string, std::string>&) -> Intentfrogsound{ return new FunpackFrogsound(); },
			nullptr
	};
	storage["funpack.lionsound"] = {
			"funpack.lionsound",
			[](const std::map<std::string, std::string>&) -> Intentlionsound{ return new FunpackLionsound(); },
			nullptr
	};
	storage["funpack.truck"] = {
			"funpack.truck",
			[](const std::map<std::string, std::string>&) -> Intenttruck{ return new FunpackTruck(); },
			nullptr
	};
	storage["funpack.angrycrowd"] = {
			"funpack.angrycrowd",
			[](const std::map<std::string, std::string>&) -> Intentangrycrowd{ return new FunpackAngrycrowd(); },
			nullptr
	};
	storage["funpack.ghost"] = {
			"funpack.ghost",
			[](const std::map<std::string, std::string>&) -> Intentghost{ return new FunpackGhost(); },
			nullptr
	};
	storage["funpack.whoiswithyou"] = {
			"funpack.whoiswithyou",
			[](const std::map<std::string, std::string>&) -> Intentwhoiswithyou{ return new FunpackWhoiswithyou(); },
			nullptr
	};
	storage["funpack.playagame"] = {
			"funpack.playagame",
			[](const std::map<std::string, std::string>&) -> Intentplayagame{ return new FunpackPlayagame(); },
			nullptr
	};
	storage["funpack.singmeasong"] = {
			"funpack.singmeasong",
			[](const std::map<std::string, std::string>&) -> Intentsingmeasong{ return new FunpackSingmeasong(); },
			nullptr
	};
	storage["funpack.beatbox"] = {
			"funpack.beatbox",
			[](const std::map<std::string, std::string>&) -> Intentbeatbox{ return new FunpackBeatbox(); },
			nullptr
	};
	storage["funpack.favoritefood"] = {
			"funpack.favoritefood",
			[](const std::map<std::string, std::string>&) -> Intentfavoritefood{ return new FunpackFavoritefood(); },
			nullptr
	};
	storage["funpack.compliment"] = {
			"funpack.compliment",
			[](const std::map<std::string, std::string>&) -> Intentcompliment{ return new FunpackCompliment(); },
			nullptr
	};
	storage["funpack.believeinlove"] = {
			"funpack.believeinlove",
			[](const std::map<std::string, std::string>&) -> Intentbelieveinlove{ return new FunpackBelieveinlove(); },
			nullptr
	};
	storage["funpack.believeinaliens"] = {
			"funpack.believeinaliens",
			[](const std::map<std::string, std::string>&) -> Intentbelieveinaliens{ return new FunpackBelieveinaliens(); },
			nullptr
	};
	storage["funpack.goodmorning"] = {
			"funpack.goodmorning",
			[](const std::map<std::string, std::string>&) -> Intentgoodmorning{ return new FunpackGoodmorning(); },
			nullptr
	};
	storage["funpack.goodevening"] = {
			"funpack.goodevening",
			[](const std::map<std::string, std::string>&) -> Intentgoodevening{ return new FunpackGoodevening(); },
			nullptr
	};
	storage["funpack.goodday"] = {
			"funpack.goodday",
			[](const std::map<std::string, std::string>&) -> Intentgoodday{ return new FunpackGoodday(); },
			nullptr
	};
	storage["funpack.goodnight"] = {
			"funpack.goodnight",
			[](const std::map<std::string, std::string>&) -> Intentgoodnight{ return new FunpackGoodnight(); },
			nullptr
	};
	storage["funpack.hi"] = {
			"funpack.hi",
			[](const std::map<std::string, std::string>&) -> Intenthi{ return new FunpackHi(); },
			nullptr
	};
	storage["funpack.isthisreallife"] = {
			"funpack.isthisreallife",
			[](const std::map<std::string, std::string>&) -> Intentisthisreallife{ return new FunpackIsthisreallife(); },
			nullptr
	};
	storage["funpack.coronavirus"] = {
			"funpack.coronavirus",
			[](const std::map<std::string, std::string>&) -> Intentcoronavirus{ return new FunpackCoronavirus(); },
			nullptr
	};
	storage["funpack.callmom"] = {
			"funpack.callmom",
			[](const std::map<std::string, std::string>&) -> Intentcallmom{ return new FunpackCallmom(); },
			nullptr
	};
	storage["funpack.callmom"] = {
			"funpack.callmom",
			[](const std::map<std::string, std::string>&) -> Intentcallmom{ return new FunpackCallmom(); },
			nullptr
	};
	storage["funpack.findphone"] = {
			"funpack.findphone",
			[](const std::map<std::string, std::string>&) -> Intentfindphone{ return new FunpackFindphone(); },
			nullptr
	};
	storage["funpack.turnlights"] = {
			"funpack.turnlights",
			[](const std::map<std::string, std::string>&) -> Intentturnlights{ return new FunpackTurnlights(); },
			nullptr
	};
	storage["funpack.settemprature"] = {
			"funpack.settemprature",
			[](const std::map<std::string, std::string>&) -> Intentsettemprature{ return new FunpackSettemprature(); },
			nullptr
	};
	storage["funpack.tv"] = {
			"funpack.tv",
			[](const std::map<std::string, std::string>&) -> Intenttv{ return new FunpackTv(); },
			nullptr
	};
	storage["funpack.buyaboat"] = {
			"funpack.buyaboat",
			[](const std::map<std::string, std::string>&) -> Intentbuyaboat{ return new FunpackBuyaboat(); },
			nullptr
	};
	storage["funpack.serande"] = {
			"funpack.serande",
			[](const std::map<std::string, std::string>&) -> Intentserande{ return new FunpackSerande(); },
			nullptr
	};
	storage["funpack.happybirthday"] = {
			"funpack.happybirthday",
			[](const std::map<std::string, std::string>&) -> Intenthappybirthday{ return new FunpackHappybirthday(); },
			nullptr
	};
	storage["funpack.celebritycrush"] = {
			"funpack.celebritycrush",
			[](const std::map<std::string, std::string>&) -> Intentcelebritycrush{ return new FunpackCelebritycrush(); },
			nullptr
	};
	storage["funpack.merrychristmas"] = {
			"funpack.merrychristmas",
			[](const std::map<std::string, std::string>&) -> Intentmerrychristmas{ return new FunpackMerrychristmas(); },
			nullptr
	};
	storage["funpack.pickupline"] = {
			"funpack.pickupline",
			[](const std::map<std::string, std::string>&) -> Intentpickupline{ return new FunpackPickupline(); },
			nullptr
	};
	storage["funpack.compliment"] = {
			"funpack.compliment",
			[](const std::map<std::string, std::string>&) -> Intentcompliment{ return new FunpackCompliment(); },
			nullptr
	};
	storage["funpack.umbrella"] = {
			"funpack.umbrella",
			[](const std::map<std::string, std::string>&) -> Intentumbrella{ return new FunpackUmbrella(); },
			nullptr
	};
	storage["funpack.secret"] = {
			"funpack.secret",
			[](const std::map<std::string, std::string>&) -> Intentsecret{ return new FunpackSecret(); },
			nullptr
	};
	storage["funpack.whatdoyouthinkofme"] = {
			"funpack.whatdoyouthinkofme",
			[](const std::map<std::string, std::string>&) -> Intentwhatdoyouthinkofme{ return new FunpackWhatdoyouthinkofme(); },
			nullptr
	};
	storage["funpack.howdoilook"] = {
			"funpack.howdoilook",
			[](const std::map<std::string, std::string>&) -> Intenthowdoilook{ return new FunpackHowdoilook(); },
			nullptr
	};
	storage["funpack.favoritekanyewestsong"] = {
			"funpack.favoritekanyewestsong",
			[](const std::map<std::string, std::string>&) -> Intentfavoritekanyewestsong{ return new FunpackFavoritekanyewestsong(); },
			nullptr
	};
	storage["funpack.highfive"] = {
			"funpack.highfive",
			[](const std::map<std::string, std::string>&) -> Intenthighfive{ return new FunpackHighfive(); },
			nullptr
	};
	storage["funpack.orderuber"] = {
			"funpack.orderuber",
			[](const std::map<std::string, std::string>&) -> Intentorderuber{ return new FunpackOrderuber(); },
			nullptr
	};
	storage["funpack.whereispassport"] = {
			"funpack.whereispassport",
			[](const std::map<std::string, std::string>&) -> Intentwhereispassport{ return new FunpackWhereispassport(); },
			nullptr
	};
	storage["funpack.whatispassword"] = {
			"funpack.whatispassword",
			[](const std::map<std::string, std::string>&) -> Intentwhatispassword{ return new FunpackWhatispassword(); },
			nullptr
	};
	storage["funpack.buyaboat"] = {
			"funpack.buyaboat",
			[](const std::map<std::string, std::string>&) -> Intentbuyaboat{ return new FunpackBuyaboat(); },
			nullptr
	};
	storage["funpack.package"] = {
			"funpack.package",
			[](const std::map<std::string, std::string>&) -> Intentpackage{ return new FunpackPackage(); },
			nullptr
	};
	storage["funpack.lonely"] = {
			"funpack.lonely",
			[](const std::map<std::string, std::string>&) -> Intentlonely{ return new FunpackLonely(); },
			nullptr
	};
	storage["funpack.dislike"] = {
			"funpack.dislike",
			[](const std::map<std::string, std::string>&) -> Intentdislike{ return new FunpackDislike(); },
			nullptr
	};
	storage["funpack.like"] = {
			"funpack.like",
			[](const std::map<std::string, std::string>&) -> Intentlike{ return new FunpackLike(); },
			nullptr
	};
	storage["funpack.actorsinmovie"] = {
			"funpack.actorsinmovie",
			[](const std::map<std::string, std::string>&) -> Intentactorsinmovie{ return new FunpackActorsinmovie(); },
			nullptr
	};
	storage["funpack.bedtimestory"] = {
			"funpack.bedtimestory",
			[](const std::map<std::string, std::string>&) -> Intentbedtimestory{ return new FunpackBedtimestory(); },
			nullptr
	};
	storage["funpack.orderitem"] = {
			"funpack.orderitem",
			[](const std::map<std::string, std::string>&) -> Intentorderitem{ return new FunpackOrderitem(); },
			nullptr
	};
	storage["funpack.scarystory"] = {
			"funpack.scarystory",
			[](const std::map<std::string, std::string>&) -> Intentscarystory{ return new FunpackScarystory(); },
			nullptr
	};
	storage["funpack.readapoem"] = {
			"funpack.readapoem",
			[](const std::map<std::string, std::string>&) -> Intentreadapoem{ return new FunpackReadapoem(); },
			nullptr
	};
	storage["funpack.whatisyourquest"] = {
			"funpack.whatisyourquest",
			[](const std::map<std::string, std::string>&) -> Intentwhatisyourquest{ return new FunpackWhatisyourquest(); },
			nullptr
	};
	storage["funpack.iamyourfather"] = {
			"funpack.iamyourfather",
			[](const std::map<std::string, std::string>&) -> Intentiamyourfather{ return new FunpackIamyourfather(); },
			nullptr
	};
	storage["funpack.areyouskynet"] = {
			"funpack.areyouskynet",
			[](const std::map<std::string, std::string>&) -> Intentareyouskynet{ return new FunpackAreyouskynet(); },
			nullptr
	};
	storage["funpack.makesandwitch"] = {
			"funpack.makesandwitch",
			[](const std::map<std::string, std::string>&) -> Intentmakesandwitch{ return new FunpackMakesandwitch(); },
			nullptr
	};
	storage["funpack.cheatcode"] = {
			"funpack.cheatcode",
			[](const std::map<std::string, std::string>&) -> Intentcheatcode{ return new FunpackCheatcode(); },
			nullptr
	};
	storage["funpack.doabarrelroll"] = {
			"funpack.doabarrelroll",
			[](const std::map<std::string, std::string>&) -> Intentdoabarrelroll{ return new FunpackDoabarrelroll(); },
			nullptr
	};
	storage["funpack.notbirthday"] = {
			"funpack.notbirthday",
			[](const std::map<std::string, std::string>&) -> Intentnotbirthday{ return new FunpackNotbirthday(); },
			nullptr
	};
	storage["funpack.didyoufart"] = {
			"funpack.didyoufart",
			[](const std::map<std::string, std::string>&) -> Intentdidyoufart{ return new FunpackDidyoufart(); },
			nullptr
	};
	storage["funpack.beammeupscotty"] = {
			"funpack.beammeupscotty",
			[](const std::map<std::string, std::string>&) -> Intentbeammeupscotty{ return new FunpackBeammeupscotty(); },
			nullptr
	};
}

const IntentInfo* IntentStore::findIntent(const char* intent){
	auto foundIntent = storage.find(intent);
	if(foundIntent == storage.end()) return nullptr;
	return &foundIntent->second;
}
