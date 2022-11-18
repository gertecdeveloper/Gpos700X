No Flutter a assinatura ocorrerá dentro da pasta Android do projeto criado. A partir daí o processo de assinatura é semelhante ao Android Nativo.
1 – No diretório “[project]/android /key.properties file” crie um arquivo key.properties que conterá as referências do certificado.

![image](https://gertecsao-my.sharepoint.com/:i:/g/personal/filipe_santos_gertec_com_br/EYD4pk1HB-NElJ6IL1U8qVwBYzR-Ujk9cfHEPXg-y6Ax-Q?e=cWPV1a)
 

2 – No arquivo de propriedades “[project]/android/app/build.gradle” adicione as informações do certificado, copiando e colando o seguinte código antes do bloco ‘android’.
 

3 – Por último, importe as chaves no mesmo arquivo gradle.
 

Na página oficial do flutter há uma documentação sobre a geração e importação desses certificados em aplicações, é possível consultá-la em: https://docs.flutter.dev/deployment/android
