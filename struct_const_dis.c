#include "base64.h"
#include "md5.h"
Outrepair_Action()
{
	//�ӿ�һ��������
	char sign_begin[200];
	char sign_md5[200];
	char sign_conn[200];
	char sign[200];
	char body[200];
	char body_json[200];
	char P_get_imei_req[200];

	//�ӿڶ���������
	char burnno_sign_begin[200];
	char burnno_sign_md5[200];
	char burnno_sign_conn[200];
	char burnno_sign[200];
	char burnno_body[200];
	char burnno_body_json[200];
	char burnno_req[200];

	//ƴ��sign���ܲ���
	lr_save_string("***","appId");
	strcpy(body,"{\"****\":\"");
	strcat(body,lr_eval_string("{test}"));
	strcat(body,"\",\"***\":\"");
	strcat(body,lr_eval_string("{oldtest}"));
	strcat(body,"\",\"applyId\":\"testApplyId\"}");
	lr_output_message("body message:%s",body);
	lr_save_string("***********","key");
	//ƴ��signԴ����Ϣ
	strcat(sign_begin,lr_eval_string("{appId}"));
	//lr_output_message("sign message:%s",sign_begin);
	strcat(sign_begin,body);
	//lr_output_message("sign message:%s",sign_begin);
	strcat(sign_begin,lr_eval_string("{key}"));
	//lr_output_message("sign message:%s",sign_begin);
	strcpy(sign_conn,sign_begin);
	//����MD5��Ϣ
	GetMd5FromString(sign_conn,sign_md5);
	lr_output_message("sign info is :%s",sign_md5);
	
	strcpy(sign,sign_md5);
	strcpy(P_get_imei_req,"{\"header\":{\"method\":\"***.method\",\"sign\":\"");
	strcat(P_get_imei_req,sign);
	strcat(P_get_imei_req,"\",\"apitype\":\"1\",\"servicetype\":0,\"appid\":\"*****\",\"operator_id\":\"**\",\"operator_name\":\"***\"},\"body\":\"");

	strcat(body_json,"{\\\"&&****\\\":\\\"");
	strcat(body_json,lr_eval_string("{test}"));
	strcat(body_json,"\\\",\\\"oldImei\\\":\\\"");
	strcat(body_json,lr_eval_string("{oldtest}"));
	strcat(body_json,"\\\",\\\"applyId\\\":\\\"testApplyId\\\"}");
	strcat(P_get_imei_req,body_json);
	strcat(P_get_imei_req,"\"}");
	lr_output_message("P_get_imei_req = %s\n",P_get_imei_req);
	
	//��̬��������**�Ĳ���
	b64_encode_string(P_get_imei_req,"P_Req_header");
	lr_output_message("������: \nNotify:\t%s",lr_eval_string("{P_Req_header}"));

	//���ϵ�
	//lr_rendezvous("***");

	lr_start_transaction("��ȡ***��");
	//ͳ�ƻ�ȡ***�ӿڵĳɹ�����
	web_reg_find("Text={\"code\":200",
				 "SaveCount=getCount",
				 LAST);
	//��ȡ���ص�****
	web_reg_save_param("getNew****",
					   "LB=****1\\\":\\\"",
					   "RB=\\\"",			
					   LAST);
	//��ȡ���ص�test
	web_reg_save_param("getNew***",
					   "LB=new***\\\":\\\"",
					   "RB=\\\"}\"}",
					   LAST);

	web_reg_save_param("errorInfo",
					   "LB={\"header",
					   "RB={}}",
					   LAST);
	web_set_max_html_param_len("402400");
	web_submit_data("getNewImei_Response",
					"Action=http://******/*****",
					"Method=POST",
                    "TargetFrame=", 
					"RecContentType=text/html",
					"Referer=http://**************/***",
					"Mode=HTML",
					ITEMDATA,
					"Name=data",
					"Value={P_Req_header}",
					ENDITEM,
					LAST);
	lr_convert_string_encoding(lr_eval_string("{errorInfo}"),"utf-8",NULL,"message");
	lr_output_message("The newImei is :%s",lr_eval_string("{getNew***}"));
	lr_output_message("The NewMeid is :%s",lr_eval_string("{getNew***}"));

	if (atoi(lr_eval_string("{getCount}")) > 0){ 
		lr_end_transaction("��ȡ***��",LR_PASS);
       } 
    else{ 
		lr_end_transaction("��ȡ***��",LR_FAIL);
    }

	//��ȡ****�ӿڷ��ص���Ϣ
	lr_start_transaction("��ȡ****�ӿڷ��ص���Ϣ");

	lr_save_string("****","burnno_appId");
	strcpy(burnno_body,"{\"*****\":\"");
	strcat(burnno_body,lr_eval_string("{test}"));
	strcat(burnno_body,"\",\"****1\":\"");
	strcat(burnno_body,lr_eval_string("{oldtest}"));
	strcat(burnno_body,"\",\"****\":\"");
	strcat(burnno_body,lr_eval_string("{oldtest}"));
	strcat(burnno_body,"\",\"*****\":\"");
	strcat(burnno_body,lr_eval_string("{oldtest}"));
	strcat(burnno_body,"\",\"****\":\"");
	strcat(burnno_body,lr_eval_string("{getNew***}"));
	strcat(burnno_body,"\",\"****\":\"");
	strcat(burnno_body,lr_eval_string("{*****}"));
	strcat(burnno_body,"\",\"PhoneCSNNew\":\"");
	strcat(burnno_body,lr_eval_string("{*****}"));
	strcat(burnno_body,"\"}");
	lr_output_message("burnno_body message:%s",burnno_body);
	lr_save_string("**************","burnno_key");
	//ƴ��signԴ����Ϣ
	strcat(burnno_sign_begin,lr_eval_string("{burnno_appId}"));
	strcat(burnno_sign_begin,burnno_body);
	strcat(burnno_sign_begin,lr_eval_string("{burnno_key}"));
	
	strcpy(burnno_sign_conn,burnno_sign_begin);
	//����MD5��Ϣ
	GetMd5FromString(burnno_sign_conn,burnno_sign_md5);
	//��̬��ȡ�ӿڽ����Ϣ�Ĳ���
	strcpy(burnno_sign,burnno_sign_md5);
	strcpy(burnno_req,"{\"header\":{\"method\":\"****.method\",\"sign\":\"");
	strcat(burnno_req,burnno_sign);
	strcat(burnno_req,"\",\"apitype\":\"1\",\"servicetype\":0,\"appid\":\"****\",\"operator_id\":\"****\",\"operator_name\":\"*****\"},\"body\":\"");
    
	strcpy(burnno_body_json,"{\\\"*****\\\":\\\"");
	strcat(burnno_body_json,lr_eval_string("{test}"));
	strcat(burnno_body_json,"\\\",\\\"****\\\":\\\"");
	strcat(burnno_body_json,lr_eval_string("{oldtest}"));
	strcat(burnno_body_json,"\\\",\\\"*****\\\":\\\"");
	strcat(burnno_body_json,lr_eval_string("{oldtest}"));
	strcat(burnno_body_json,"\\\",\\\"****\\\":\\\"");
	strcat(burnno_body_json,lr_eval_string("{oldtest}"));
	strcat(burnno_body_json,"\\\",\\\"****\\\":\\\"");
	strcat(burnno_body_json,lr_eval_string("{getNew****}"));
	strcat(burnno_body_json,"\\\",\\\"*****\\\":\\\"");
	strcat(burnno_body_json,lr_eval_string("{****}"));
	strcat(burnno_body_json,"\\\",\\\"****\\\":\\\"");
	strcat(burnno_body_json,lr_eval_string("{****}"));
	strcat(burnno_body_json,"\\\"}");
	strcat(burnno_req,burnno_body_json);
	strcat(burnno_req,"\"}");

	lr_output_message("****.**** = %s\n",burnno_req);
	b64_encode_string(burnno_req,"P_req_header");
	lr_output_message("The Message is: %s\n",lr_eval_string("{P_req_header}"));
	//��ȡ**���ص���Ϣ
	web_reg_find("Text={\"code\":200",
				 "SaveCount=getCountInfo",
				 LAST);
	web_submit_data("get****",
					"Action=http://******/***api",
					"Method=POST",
					"TargetFrame=",
					"RecContentType=text/html",
					"Referer=http://*******/*****api",
					"Mode=HTML",
					ITEMDATA,
					"Name=data","Value={P_req_header}", ENDITEM,
					LAST);
	if (atoi(lr_eval_string("{getCountInfo}")) > 0){
		lr_end_transaction("��ȡ***���ص���Ϣ",LR_PASS);
       } 
    else{
		lr_end_transaction("��ȡ****���ص���Ϣ",LR_FAIL);
    }

	//���³�ʼ������
	memset(sign_begin,0,sizeof(sign_begin)/sizeof(char));
	memset(sign_md5,0,sizeof(sign_md5)/sizeof(char));
	memset(sign_conn,0,sizeof(sign_conn)/sizeof(char));
	memset(sign,0,sizeof(sign)/sizeof(char));
	memset(body,0,sizeof(body)/sizeof(char));
	memset(body_json,0,sizeof(body_json)/sizeof(char));
	memset(P_get_imei_req,0,sizeof(P_get_imei_req)/sizeof(char));

	memset(burnno_sign_begin,0,sizeof(burnno_sign_begin)/sizeof(char));
	memset(burnno_sign_md5,0,sizeof(burnno_sign_md5)/sizeof(char));
	memset(burnno_sign_conn,0,sizeof(burnno_sign_conn)/sizeof(char));
	memset(burnno_sign,0,sizeof(burnno_sign)/sizeof(char));
	memset(burnno_body,0,sizeof(burnno_body)/sizeof(char));
	memset(burnno_body_json,0,sizeof(burnno_body_json)/sizeof(char));
	memset(burnno_req,0,sizeof(burnno_req)/sizeof(char));
	
	return 0;
}

