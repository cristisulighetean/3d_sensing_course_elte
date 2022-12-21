
Report of Data-Level fusion homework
====================================

Contents
========

* [Overview](#overview)
* [Directories tested](#directories-tested)
	* [s11_lampshade2](#s11_lampshade2)
	* [s3_baby2](#s3_baby2)
	* [s10_lampshade1](#s10_lampshade1)
	* [s4_bowling1](#s4_bowling1)
	* [s12_plastic](#s12_plastic)
	* [s7_cloth3](#s7_cloth3)
	* [s1_aloe](#s1_aloe)
	* [s5_bowling2](#s5_bowling2)
	* [s6_cloth2](#s6_cloth2)
	* [s9_flowerpots](#s9_flowerpots)
	* [s8_cloth4](#s8_cloth4)
	* [s2_baby1](#s2_baby1)

# Overview


This file consists of the evaluation report for the Data-level fusion homework. 12 pairs of half-sized images have been taken from the 2006 Stereo Dataset and tested.

This report will look into the each pair of images and output the following:  
  - Output of the upsampling algorithm  
  - Table with the metrics resulted from the comparison of the `Ground Truth` with the `Bilateral Filter` output as well as the processing time  
  - Best image and the sigma choice for each metric tested.


# Directories tested

## s11_lampshade2

### Upsampling result
  
<p align="center">
    <img src="./data/s11_lampshade2/eval/upsampled_image.png" width="300" height="300"/>
</p>


### Resulted metrics
  

|File Name|Spatial Sigma|Spectral Sigma|Time(MS)|SSD|RMSE|PSNR|SSIM|
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
|0|0.1|1.0|222.0|227638437.0|25.120000|20.130411|0.205323|
|1|0.1|3.0|224.0|227649515.0|25.120611|20.130200|0.204578|
|2|0.1|5.0|225.0|227669849.0|25.121733|20.129812|0.191069|
|3|0.1|10.0|225.0|227655406.0|25.120936|20.130087|0.192951|
|4|1.0|1.0|225.0|204817272.0|23.827590|20.589201|0.215445|
|5|1.0|3.0|225.0|210101233.0|24.132990|20.478581|0.213477|
|6|1.0|5.0|225.0|214473150.0|24.382784|20.389138|0.212687|
|7|1.0|10.0|222.0|217014689.0|24.526829|20.337976|0.212185|
|8|1.5|1.0|222.0|204565383.0|23.812934|20.594546|0.216268|
|9|1.5|3.0|223.0|206883532.0|23.947478|20.545608|0.215233|
|10|1.5|5.0|221.0|209740132.0|24.112242|20.486052|0.215016|
|11|1.5|10.0|221.0|212084085.0|24.246601|20.437786|0.214551|
|12|3.0|1.0|221.0|204482672.0|23.808119|20.596302|0.217013|
|13|3.0|3.0|221.0|205425429.0|23.862939|20.576325|0.215586|
|14|3.0|5.0|221.0|206727107.0|23.938423|20.548893|0.215723|
|15|3.0|10.0|221.0|208206015.0|24.023897|20.517934|0.215620|

### Best processing time


Spatial Sigma: 1.5 . Spectral Sigma: 5.0  
<p align="center">
    <img src="./data/s11_lampshade2/eval/10.png" width="300" height="300"/>
</p>


### Best SSD value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s11_lampshade2/eval/12.png" width="300" height="300"/>
</p>


### Best RMSE value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s11_lampshade2/eval/12.png" width="300" height="300"/>
</p>


### Best PSNR value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s11_lampshade2/eval/12.png" width="300" height="300"/>
</p>


### Best SSIM value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s11_lampshade2/eval/12.png" width="300" height="300"/>
</p>


## s3_baby2

### Upsampling result
  
<p align="center">
    <img src="./data/s3_baby2/eval/upsampled_image.png" width="300" height="300"/>
</p>


### Resulted metrics
  

|File Name|Spatial Sigma|Spectral Sigma|Time(MS)|SSD|RMSE|PSNR|SSIM|
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
|0|0.1|1.0|215.0|185421939.0|23.213372|20.816039|1.472933|
|1|0.1|3.0|215.0|185585182.0|23.223588|20.812217|1.405502|
|2|0.1|5.0|214.0|185601426.0|23.224604|20.811837|1.382860|
|3|0.1|10.0|211.0|185560891.0|23.222068|20.812786|1.518707|
|4|1.0|1.0|211.0|119584261.0|18.642093|22.720910|1.447066|
|5|1.0|3.0|214.0|135665158.0|19.856003|22.172967|1.429996|
|6|1.0|5.0|215.0|147388942.0|20.696176|21.813001|1.422661|
|7|1.0|10.0|215.0|155306178.0|21.244770|21.585763|1.419605|
|8|1.5|1.0|221.0|119033355.0|18.599103|22.740964|1.449715|
|9|1.5|3.0|211.0|126426879.0|19.168025|22.479256|1.438645|
|10|1.5|5.0|212.0|134000932.0|19.733839|22.226572|1.433706|
|11|1.5|10.0|212.0|140981054.0|20.241283|22.006043|1.430134|
|12|3.0|1.0|214.0|118884034.0|18.587434|22.746415|1.452278|
|13|3.0|3.0|216.0|121992274.0|18.828851|22.634327|1.446011|
|14|3.0|5.0|213.0|125779664.0|19.118899|22.501546|1.441233|
|15|3.0|10.0|214.0|129993249.0|19.436500|22.358442|1.437020|

### Best processing time


Spatial Sigma: 0.1 . Spectral Sigma: 10.0  
<p align="center">
    <img src="./data/s3_baby2/eval/3.png" width="300" height="300"/>
</p>


### Best SSD value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s3_baby2/eval/12.png" width="300" height="300"/>
</p>


### Best RMSE value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s3_baby2/eval/12.png" width="300" height="300"/>
</p>


### Best PSNR value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s3_baby2/eval/12.png" width="300" height="300"/>
</p>


### Best SSIM value


Spatial Sigma: 0.1 . Spectral Sigma: 10.0  
<p align="center">
    <img src="./data/s3_baby2/eval/3.png" width="300" height="300"/>
</p>


## s10_lampshade1

### Upsampling result
  
<p align="center">
    <img src="./data/s10_lampshade1/eval/upsampled_image.png" width="300" height="300"/>
</p>


### Resulted metrics
  

|File Name|Spatial Sigma|Spectral Sigma|Time(MS)|SSD|RMSE|PSNR|SSIM|
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
|0|0.1|1.0|226.0|223931718.0|24.914641|20.201711|0.273020|
|1|0.1|3.0|229.0|223916628.0|24.913802|20.202004|0.267492|
|2|0.1|5.0|225.0|223938296.0|24.915007|20.201583|0.273970|
|3|0.1|10.0|222.0|223936293.0|24.914896|20.201622|0.271272|
|4|1.0|1.0|227.0|191840346.0|23.060398|20.873468|0.282751|
|5|1.0|3.0|224.0|199075678.0|23.491239|20.712685|0.278963|
|6|1.0|5.0|225.0|205453484.0|23.864568|20.575732|0.277183|
|7|1.0|10.0|222.0|209005009.0|24.069949|20.501300|0.276702|
|8|1.5|1.0|222.0|191542569.0|23.042494|20.880214|0.281899|
|9|1.5|3.0|222.0|194631207.0|23.227532|20.810742|0.280818|
|10|1.5|5.0|224.0|198672422.0|23.467435|20.721491|0.279982|
|11|1.5|10.0|225.0|201975346.0|23.661704|20.649883|0.279496|
|12|3.0|1.0|225.0|191444029.0|23.036566|20.882449|0.282633|
|13|3.0|3.0|225.0|192627321.0|23.107650|20.855688|0.281378|
|14|3.0|5.0|225.0|194363786.0|23.211569|20.816714|0.281262|
|15|3.0|10.0|226.0|196387361.0|23.332088|20.771732|0.280809|

### Best processing time


Spatial Sigma: 0.1 . Spectral Sigma: 10.0  
<p align="center">
    <img src="./data/s10_lampshade1/eval/3.png" width="300" height="300"/>
</p>


### Best SSD value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s10_lampshade1/eval/12.png" width="300" height="300"/>
</p>


### Best RMSE value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s10_lampshade1/eval/12.png" width="300" height="300"/>
</p>


### Best PSNR value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s10_lampshade1/eval/12.png" width="300" height="300"/>
</p>


### Best SSIM value


Spatial Sigma: 1.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s10_lampshade1/eval/4.png" width="300" height="300"/>
</p>


## s4_bowling1

### Upsampling result
  
<p align="center">
    <img src="./data/s4_bowling1/eval/upsampled_image.png" width="300" height="300"/>
</p>


### Resulted metrics
  

|File Name|Spatial Sigma|Spectral Sigma|Time(MS)|SSD|RMSE|PSNR|SSIM|
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
|0|0.1|1.0|218.0|277651712.0|28.269395|19.104473|0.381043|
|1|0.1|3.0|217.0|277670223.0|28.270338|19.104184|0.393776|
|2|0.1|5.0|220.0|277680219.0|28.270847|19.104027|0.383388|
|3|0.1|10.0|219.0|277658713.0|28.269752|19.104364|0.367962|
|4|1.0|1.0|217.0|230777226.0|25.772872|19.907547|0.404790|
|5|1.0|3.0|218.0|239303658.0|26.244664|19.749983|0.399048|
|6|1.0|5.0|216.0|249278500.0|26.786055|19.572629|0.397346|
|7|1.0|10.0|217.0|255806436.0|27.134516|19.460362|0.395805|
|8|1.5|1.0|217.0|230411113.0|25.752420|19.914443|0.405119|
|9|1.5|3.0|217.0|234036280.0|25.954217|19.846645|0.402753|
|10|1.5|5.0|217.0|239479932.0|26.254328|19.746786|0.400987|
|11|1.5|10.0|214.0|245250461.0|26.568758|19.643378|0.399666|
|12|3.0|1.0|213.0|230303640.0|25.746414|19.916469|0.405498|
|13|3.0|3.0|213.0|231792572.0|25.829506|19.888482|0.405506|
|14|3.0|5.0|213.0|233838572.0|25.943252|19.850315|0.404324|
|15|3.0|10.0|213.0|236972094.0|26.116498|19.792505|0.403216|

### Best processing time


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s4_bowling1/eval/12.png" width="300" height="300"/>
</p>


### Best SSD value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s4_bowling1/eval/12.png" width="300" height="300"/>
</p>


### Best RMSE value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s4_bowling1/eval/12.png" width="300" height="300"/>
</p>


### Best PSNR value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s4_bowling1/eval/12.png" width="300" height="300"/>
</p>


### Best SSIM value


Spatial Sigma: 3.0 . Spectral Sigma: 3.0  
<p align="center">
    <img src="./data/s4_bowling1/eval/13.png" width="300" height="300"/>
</p>


## s12_plastic

### Upsampling result
  
<p align="center">
    <img src="./data/s12_plastic/eval/upsampled_image.png" width="300" height="300"/>
</p>


### Resulted metrics
  

|File Name|Spatial Sigma|Spectral Sigma|Time(MS)|SSD|RMSE|PSNR|SSIM|
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
|0|0.1|1.0|217.0|144180173.0|20.226438|22.012415|0.617996|
|1|0.1|3.0|217.0|144185199.0|20.226791|22.012264|0.606200|
|2|0.1|5.0|217.0|144207527.0|20.228357|22.011591|0.561960|
|3|0.1|10.0|219.0|144223731.0|20.229493|22.011103|0.620632|
|4|1.0|1.0|222.0|114863237.0|18.053324|22.999660|0.554893|
|5|1.0|3.0|220.0|118360582.0|18.326106|22.869400|0.552524|
|6|1.0|5.0|220.0|124365223.0|18.785213|22.654481|0.556733|
|7|1.0|10.0|221.0|129626074.0|19.178420|22.474547|0.556874|
|8|1.5|1.0|220.0|114705155.0|18.040896|23.005641|0.552768|
|9|1.5|3.0|220.0|116184009.0|18.156822|22.950007|0.556190|
|10|1.5|5.0|220.0|118912161.0|18.368758|22.849208|0.556222|
|11|1.5|10.0|221.0|122998744.0|18.681725|22.702464|0.556113|
|12|3.0|1.0|220.0|114642473.0|18.035966|23.008015|0.556308|
|13|3.0|3.0|221.0|115231295.0|18.082225|22.985766|0.551727|
|14|3.0|5.0|219.0|116033953.0|18.145093|22.955620|0.554141|
|15|3.0|10.0|221.0|117791354.0|18.281985|22.890337|0.553753|

### Best processing time


Spatial Sigma: 0.1 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s12_plastic/eval/0.png" width="300" height="300"/>
</p>


### Best SSD value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s12_plastic/eval/12.png" width="300" height="300"/>
</p>


### Best RMSE value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s12_plastic/eval/12.png" width="300" height="300"/>
</p>


### Best PSNR value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s12_plastic/eval/12.png" width="300" height="300"/>
</p>


### Best SSIM value


Spatial Sigma: 0.1 . Spectral Sigma: 10.0  
<p align="center">
    <img src="./data/s12_plastic/eval/3.png" width="300" height="300"/>
</p>


## s7_cloth3

### Upsampling result
  
<p align="center">
    <img src="./data/s7_cloth3/eval/upsampled_image.png" width="300" height="300"/>
</p>


### Resulted metrics
  

|File Name|Spatial Sigma|Spectral Sigma|Time(MS)|SSD|RMSE|PSNR|SSIM|
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
|0|0.1|1.0|214.0|247247295.0|26.676701|19.608161|0.798803|
|1|0.1|3.0|215.0|247297364.0|26.679402|19.607282|0.793371|
|2|0.1|5.0|215.0|247294603.0|26.679253|19.607330|0.799300|
|3|0.1|10.0|215.0|247336299.0|26.681502|19.606598|0.803494|
|4|1.0|1.0|217.0|124650655.0|18.941468|22.582531|0.865297|
|5|1.0|3.0|215.0|162033065.0|21.595744|21.443440|0.829429|
|6|1.0|5.0|219.0|183356764.0|22.972846|20.906507|0.818798|
|7|1.0|10.0|219.0|193723907.0|23.613369|20.667645|0.812008|
|8|1.5|1.0|217.0|123789838.0|18.875951|22.612627|0.868340|
|9|1.5|3.0|216.0|140333035.0|20.097697|22.067878|0.840012|
|10|1.5|5.0|217.0|156123513.0|21.198274|21.604794|0.824101|
|11|1.5|10.0|217.0|166632761.0|21.900122|21.321873|0.818546|
|12|3.0|1.0|217.0|123594271.0|18.861035|22.619493|0.868352|
|13|3.0|3.0|218.0|130477012.0|19.379088|22.384137|0.839255|
|14|3.0|5.0|217.0|137929861.0|19.924870|22.142894|0.827773|
|15|3.0|10.0|217.0|144530271.0|20.396035|21.939889|0.820599|

### Best processing time


Spatial Sigma: 0.1 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s7_cloth3/eval/0.png" width="300" height="300"/>
</p>


### Best SSD value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s7_cloth3/eval/12.png" width="300" height="300"/>
</p>


### Best RMSE value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s7_cloth3/eval/12.png" width="300" height="300"/>
</p>


### Best PSNR value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s7_cloth3/eval/12.png" width="300" height="300"/>
</p>


### Best SSIM value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s7_cloth3/eval/12.png" width="300" height="300"/>
</p>


## s1_aloe

### Upsampling result
  
<p align="center">
    <img src="./data/s1_aloe/eval/upsampled_image.png" width="300" height="300"/>
</p>


### Resulted metrics
  

|File Name|Spatial Sigma|Spectral Sigma|Time(MS)|SSD|RMSE|PSNR|SSIM|
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
|0|0.1|1.0|222.0|338598168.0|30.850826|18.345468|0.382498|
|1|0.1|3.0|221.0|338851099.0|30.862347|18.342225|0.386204|
|2|0.1|5.0|223.0|338849729.0|30.862284|18.342242|0.384940|
|3|0.1|10.0|222.0|338898029.0|30.864484|18.341623|0.381771|
|4|1.0|1.0|222.0|171229710.0|21.938860|21.306523|0.461362|
|5|1.0|3.0|221.0|219621037.0|24.846285|20.225574|0.423174|
|6|1.0|5.0|220.0|252260583.0|26.628653|19.623820|0.408328|
|7|1.0|10.0|225.0|269181255.0|27.507233|19.341866|0.402458|
|8|1.5|1.0|221.0|170391944.0|21.885125|21.327823|0.463207|
|9|1.5|3.0|221.0|191884766.0|23.224413|20.811909|0.432687|
|10|1.5|5.0|222.0|216883947.0|24.690973|20.280040|0.418158|
|11|1.5|10.0|218.0|234336379.0|25.665182|19.943917|0.410855|
|12|3.0|1.0|221.0|170201114.0|21.872866|21.332690|0.462589|
|13|3.0|3.0|221.0|179890331.0|22.486839|21.092236|0.438654|
|14|3.0|5.0|221.0|194625819.0|23.389704|20.750309|0.421917|
|15|3.0|10.0|221.0|207601422.0|24.156814|20.470010|0.411570|

### Best processing time


Spatial Sigma: 1.5 . Spectral Sigma: 10.0  
<p align="center">
    <img src="./data/s1_aloe/eval/11.png" width="300" height="300"/>
</p>


### Best SSD value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s1_aloe/eval/12.png" width="300" height="300"/>
</p>


### Best RMSE value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s1_aloe/eval/12.png" width="300" height="300"/>
</p>


### Best PSNR value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s1_aloe/eval/12.png" width="300" height="300"/>
</p>


### Best SSIM value


Spatial Sigma: 1.5 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s1_aloe/eval/8.png" width="300" height="300"/>
</p>


## s5_bowling2

### Upsampling result
  
<p align="center">
    <img src="./data/s5_bowling2/eval/upsampled_image.png" width="300" height="300"/>
</p>


### Resulted metrics
  

|File Name|Spatial Sigma|Spectral Sigma|Time(MS)|SSD|RMSE|PSNR|SSIM|
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
|0|0.1|1.0|229.0|195398800.0|23.009312|20.892731|0.692781|
|1|0.1|3.0|228.0|195404887.0|23.009670|20.892596|0.693277|
|2|0.1|5.0|228.0|195413171.0|23.010158|20.892412|0.692629|
|3|0.1|10.0|230.0|195424199.0|23.010807|20.892166|0.697839|
|4|1.0|1.0|229.0|123709090.0|18.308109|22.877934|0.730742|
|5|1.0|3.0|229.0|139016875.0|19.407806|22.371275|0.721488|
|6|1.0|5.0|230.0|153710812.0|20.407739|21.934906|0.714431|
|7|1.0|10.0|230.0|162656410.0|20.993182|21.689238|0.711244|
|8|1.5|1.0|233.0|123143220.0|18.266189|22.897845|0.731499|
|9|1.5|3.0|231.0|129717787.0|18.747461|22.671955|0.723669|
|10|1.5|5.0|234.0|138427829.0|19.366645|22.389716|0.718033|
|11|1.5|10.0|228.0|146615434.0|19.931158|22.140153|0.713796|
|12|3.0|1.0|230.0|122983752.0|18.254358|22.903473|0.733465|
|13|3.0|3.0|230.0|125725511.0|18.456714|22.807716|0.727597|
|14|3.0|5.0|230.0|129229465.0|18.712140|22.688334|0.722607|
|15|3.0|10.0|230.0|133876611.0|19.045617|22.534903|0.720367|

### Best processing time


Spatial Sigma: 0.1 . Spectral Sigma: 3.0  
<p align="center">
    <img src="./data/s5_bowling2/eval/1.png" width="300" height="300"/>
</p>


### Best SSD value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s5_bowling2/eval/12.png" width="300" height="300"/>
</p>


### Best RMSE value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s5_bowling2/eval/12.png" width="300" height="300"/>
</p>


### Best PSNR value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s5_bowling2/eval/12.png" width="300" height="300"/>
</p>


### Best SSIM value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s5_bowling2/eval/12.png" width="300" height="300"/>
</p>


## s6_cloth2

### Upsampling result
  
<p align="center">
    <img src="./data/s6_cloth2/eval/upsampled_image.png" width="300" height="300"/>
</p>


### Resulted metrics
  

|File Name|Spatial Sigma|Spectral Sigma|Time(MS)|SSD|RMSE|PSNR|SSIM|
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
|0|0.1|1.0|226.0|229367475.0|25.215219|20.097549|0.361234|
|1|0.1|3.0|225.0|229382955.0|25.216070|20.097256|0.367488|
|2|0.1|5.0|225.0|229387508.0|25.216320|20.097169|0.365517|
|3|0.1|10.0|225.0|229377549.0|25.215773|20.097358|0.361752|
|4|1.0|1.0|225.0|141870985.0|19.830955|22.183931|0.388914|
|5|1.0|3.0|225.0|168810170.0|21.631973|21.428881|0.381740|
|6|1.0|5.0|225.0|183633874.0|22.561773|21.063339|0.369987|
|7|1.0|10.0|225.0|191726892.0|23.053578|20.876037|0.369221|
|8|1.5|1.0|225.0|141062273.0|19.774352|22.208758|0.389838|
|9|1.5|3.0|227.0|153832504.0|20.650039|21.832386|0.386779|
|10|1.5|5.0|226.0|164691921.0|21.366480|21.536144|0.375071|
|11|1.5|10.0|225.0|172616920.0|21.874519|21.332033|0.372945|
|12|3.0|1.0|225.0|140859289.0|19.760120|22.215012|0.389888|
|13|3.0|3.0|225.0|146544241.0|20.154926|22.043179|0.388427|
|14|3.0|5.0|225.0|152573620.0|20.565371|21.868073|0.376987|
|15|3.0|10.0|225.0|157719453.0|20.909298|21.724014|0.374757|

### Best processing time


Spatial Sigma: 0.1 . Spectral Sigma: 3.0  
<p align="center">
    <img src="./data/s6_cloth2/eval/1.png" width="300" height="300"/>
</p>


### Best SSD value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s6_cloth2/eval/12.png" width="300" height="300"/>
</p>


### Best RMSE value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s6_cloth2/eval/12.png" width="300" height="300"/>
</p>


### Best PSNR value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s6_cloth2/eval/12.png" width="300" height="300"/>
</p>


### Best SSIM value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s6_cloth2/eval/12.png" width="300" height="300"/>
</p>


## s9_flowerpots

### Upsampling result
  
<p align="center">
    <img src="./data/s9_flowerpots/eval/upsampled_image.png" width="300" height="300"/>
</p>


### Resulted metrics
  

|File Name|Spatial Sigma|Spectral Sigma|Time(MS)|SSD|RMSE|PSNR|SSIM|
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
|0|0.1|1.0|227.0|97541516.0|16.368027|23.850877|0.528319|
|1|0.1|3.0|227.0|97701263.0|16.381425|23.843770|0.523980|
|2|0.1|5.0|227.0|97704745.0|16.381717|23.843615|0.523912|
|3|0.1|10.0|227.0|97706305.0|16.381848|23.843546|0.525937|
|4|1.0|1.0|227.0|51652225.0|11.910942|26.611881|0.551738|
|5|1.0|3.0|227.0|58939440.0|12.723441|26.038712|0.545799|
|6|1.0|5.0|227.0|68272767.0|13.693843|25.400297|0.542741|
|7|1.0|10.0|227.0|75052341.0|14.357662|24.989129|0.540219|
|8|1.5|1.0|227.0|51168219.0|11.855005|26.652769|0.553915|
|9|1.5|3.0|228.0|54213089.0|12.202636|26.401730|0.548974|
|10|1.5|5.0|231.0|58873585.0|12.716331|26.043567|0.545510|
|11|1.5|10.0|229.0|64520518.0|13.312221|25.645793|0.543098|
|12|3.0|1.0|227.0|51012944.0|11.837004|26.665968|0.554723|
|13|3.0|3.0|228.0|51990332.0|11.949862|26.583546|0.549605|
|14|3.0|5.0|227.0|53223999.0|12.090808|26.481697|0.546716|
|15|3.0|10.0|228.0|55937914.0|12.395234|26.265709|0.543113|

### Best processing time


Spatial Sigma: 0.1 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s9_flowerpots/eval/0.png" width="300" height="300"/>
</p>


### Best SSD value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s9_flowerpots/eval/12.png" width="300" height="300"/>
</p>


### Best RMSE value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s9_flowerpots/eval/12.png" width="300" height="300"/>
</p>


### Best PSNR value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s9_flowerpots/eval/12.png" width="300" height="300"/>
</p>


### Best SSIM value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s9_flowerpots/eval/12.png" width="300" height="300"/>
</p>


## s8_cloth4

### Upsampling result
  
<p align="center">
    <img src="./data/s8_cloth4/eval/upsampled_image.png" width="300" height="300"/>
</p>


### Resulted metrics
  

|File Name|Spatial Sigma|Spectral Sigma|Time(MS)|SSD|RMSE|PSNR|SSIM|
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
|0|0.1|1.0|225.0|320439263.0|29.803666|18.645410|0.459361|
|1|0.1|3.0|225.0|320453305.0|29.804319|18.645219|0.457120|
|2|0.1|5.0|225.0|320454391.0|29.804370|18.645205|0.459879|
|3|0.1|10.0|225.0|320480777.0|29.805597|18.644847|0.461271|
|4|1.0|1.0|229.0|166923087.0|21.510724|21.477703|0.518655|
|5|1.0|3.0|225.0|215054429.0|24.415804|20.377383|0.490174|
|6|1.0|5.0|225.0|243748590.0|25.993687|19.833446|0.481500|
|7|1.0|10.0|225.0|257730505.0|26.728817|19.591209|0.477617|
|8|1.5|1.0|225.0|166061450.0|21.455135|21.500179|0.519731|
|9|1.5|3.0|225.0|186899558.0|22.761505|20.986784|0.499165|
|10|1.5|5.0|226.0|209561028.0|24.101945|20.489762|0.491903|
|11|1.5|10.0|230.0|224213234.0|24.930297|20.196255|0.487551|
|12|3.0|1.0|227.0|165857990.0|21.441987|21.505503|0.519843|
|13|3.0|3.0|226.0|174356386.0|21.984458|21.288488|0.503948|
|14|3.0|5.0|226.0|187022511.0|22.768990|20.983928|0.497616|
|15|3.0|10.0|290.0|197775944.0|23.414429|20.741132|0.492932|

### Best processing time


Spatial Sigma: 0.1 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s8_cloth4/eval/0.png" width="300" height="300"/>
</p>


### Best SSD value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s8_cloth4/eval/12.png" width="300" height="300"/>
</p>


### Best RMSE value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s8_cloth4/eval/12.png" width="300" height="300"/>
</p>


### Best PSNR value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s8_cloth4/eval/12.png" width="300" height="300"/>
</p>


### Best SSIM value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s8_cloth4/eval/12.png" width="300" height="300"/>
</p>


## s2_baby1

### Upsampling result
  
<p align="center">
    <img src="./data/s2_baby1/eval/upsampled_image.png" width="300" height="300"/>
</p>


### Resulted metrics
  

|File Name|Spatial Sigma|Spectral Sigma|Time(MS)|SSD|RMSE|PSNR|SSIM|
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
|0|0.1|1.0|215.0|201876181.0|24.221454|20.446800|0.179570|
|1|0.1|3.0|215.0|201885809.0|24.222031|20.446592|0.179177|
|2|0.1|5.0|216.0|201872604.0|24.221239|20.446876|0.178829|
|3|0.1|10.0|216.0|201882880.0|24.221856|20.446655|0.178814|
|4|1.0|1.0|215.0|143157982.0|20.396960|21.939495|0.207378|
|5|1.0|3.0|214.0|161110731.0|21.638139|21.426406|0.195381|
|6|1.0|5.0|214.0|171358378.0|22.315691|21.158597|0.192158|
|7|1.0|10.0|214.0|176450197.0|22.644813|21.031429|0.190654|
|8|1.5|1.0|215.0|142606982.0|20.357669|21.956242|0.208996|
|9|1.5|3.0|214.0|150839103.0|20.937009|21.712511|0.199416|
|10|1.5|5.0|215.0|158808433.0|21.482976|21.488915|0.195942|
|11|1.5|10.0|214.0|164036810.0|21.833749|21.348237|0.194021|
|12|3.0|1.0|218.0|142453226.0|20.346692|21.960927|0.209559|
|13|3.0|3.0|217.0|145973744.0|20.596576|21.854903|0.200174|
|14|3.0|5.0|215.0|150590307.0|20.919735|21.719680|0.197381|
|15|3.0|10.0|215.0|154490989.0|21.188940|21.608619|0.195815|

### Best processing time


Spatial Sigma: 1.0 . Spectral Sigma: 3.0  
<p align="center">
    <img src="./data/s2_baby1/eval/5.png" width="300" height="300"/>
</p>


### Best SSD value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s2_baby1/eval/12.png" width="300" height="300"/>
</p>


### Best RMSE value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s2_baby1/eval/12.png" width="300" height="300"/>
</p>


### Best PSNR value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s2_baby1/eval/12.png" width="300" height="300"/>
</p>


### Best SSIM value


Spatial Sigma: 3.0 . Spectral Sigma: 1.0  
<p align="center">
    <img src="./data/s2_baby1/eval/12.png" width="300" height="300"/>
</p>

