/**
* @file   : task.h
* @brief  : ����Ļ����࣬������������Ľӿ�
* @version: 1.0
* @author : ��³��
* @create : 2017��04��
* @date   : 2017��6��3��
* @note   : ���� Apache ����֤ 2.0 �棨���¼�ơ�����֤������Ȩ;
*           �������ر����ɣ�����������ʹ������ļ���
* @remarks: �����Ի�ø����ɵĸ�����
*           http://www.apache.org/licenses/LICENSE-2.0
*           �������÷�����Ҫ��������ͬ�⣬�������ɷַ�������
*           Ҫ����ԭ�����ַ���û���κ���ʽ�ģ���ȷ�������ĵ������
*           �μ����ձ����ɿ�������Ȩ�޼����Ƶ��ض����Ե�����֤��
*
*   ����Ի�øô�������°汾��
*
*        http://git.oschina.net/Mr_ChenLuYong/oeasypool
*
*   ��Դ�����������˶��ڴ�����Ĺ�ͬά����
*
*
*   ��������Щ���뻹�в�����ĵط�����ͨ�����µ����½���ѧϰ��
*
*        ���͵�ַ��http://blog.csdn.net/csnd_ayo
*
*        ���µ�ַ��http://blog.csdn.net/csnd_ayo/article/details/72457190
*
* 	 �ڴ����ύBug����ӭIssues��
*
*/


#ifndef __OETASK_H__
#define __OETASK_H__

#include <time.h>
#include <atomic>

namespace HL
{
	// �������
	class HLTask
	{

	protected:

		// �����Ψһ��ʶ
		size_t                      id_;
		// ���񴴽�ʱ�� ����Unixʱ�����
		clock_t                     createTime_;

	private:

		static std::atomic<size_t>  nRequestID_;
		// ����ȡ��״̬
		std::atomic<bool>           isCancelRequired_;

	public:
		HLTask(void) :id_(nRequestID_++), isCancelRequired_(false),
			createTime_(clock()) {}
		virtual ~HLTask(void) {};

	public:
		// ��������ӿڣ��̳������ı���Ҫʵ������ӿ�
		virtual int doWork(void) = 0;

		// ������ȡ���ص�
		virtual int onCanceled(void) { return 1; }
		// ���������
		virtual int onCompleted(int) { return 1; }

		// �����Ƿ�ʱ
		virtual bool isTimeout(const clock_t& now) {
			return ((now - createTime_) > 5000);
		}

		// ��ȡ����ID
		size_t getID(void) { return id_; }
		// ��ȡ����ȡ��״̬
		bool isCancelRequired(void) { return isCancelRequired_; }
		// ��������ȡ��״̬
		void setCancelRequired(void) { isCancelRequired_ = true; }


	};

	__declspec(selectany) std::atomic<size_t> HLTask::nRequestID_ = 100000;
}

#endif // __OETASK_H__