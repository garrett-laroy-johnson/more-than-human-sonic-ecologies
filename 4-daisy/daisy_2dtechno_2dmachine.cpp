#include "daisy_2dtechno_2dmachine.h"

namespace daisy_2dtechno_2dmachine {

/****************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER 200k USD in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below 200k USD annual revenue or funding.

For entities with OVER 200k USD in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing (at) cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/360050779193-Gen-Code-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
****************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Change __m_change_15;
	Change __m_change_14;
	Change __m_change_48;
	Change __m_change_17;
	Change __m_change_12;
	Change __m_change_55;
	Change __m_change_62;
	Change __m_change_20;
	Change __m_change_27;
	Change __m_change_34;
	Change __m_change_69;
	Change __m_change_41;
	Delta __m_delta_13;
	Phasor __m_phasor_11;
	PlusEquals __m_pluseq_16;
	SineCycle __m_cycle_33;
	SineCycle __m_cycle_47;
	SineCycle __m_cycle_26;
	SineCycle __m_cycle_19;
	SineCycle __m_cycle_40;
	SineCycle __m_cycle_68;
	SineCycle __m_cycle_61;
	SineCycle __m_cycle_54;
	SineData __sinedata;
	int __exception;
	int vectorsize;
	t_sample __m_slide_43;
	t_sample __m_latch_42;
	t_sample __m_latch_46;
	t_sample __m_latch_67;
	t_sample __m_latch_63;
	t_sample __m_latch_49;
	t_sample __m_latch_53;
	t_sample __m_slide_64;
	t_sample __m_slide_57;
	t_sample __m_slide_50;
	t_sample __m_latch_60;
	t_sample __m_latch_56;
	t_sample __m_latch_28;
	t_sample __m_slide_36;
	t_sample m_history_5;
	t_sample m_history_6;
	t_sample m_history_7;
	t_sample m_knob_8;
	t_sample m_history_4;
	t_sample m_history_2;
	t_sample m_history_3;
	t_sample samplerate;
	t_sample m_history_1;
	t_sample __m_latch_39;
	t_sample m_knob_9;
	t_sample samples_to_seconds;
	t_sample __m_slide_29;
	t_sample __m_latch_32;
	t_sample __m_latch_35;
	t_sample m_button_10;
	t_sample __m_latch_70;
	t_sample __m_slide_22;
	t_sample __m_latch_25;
	t_sample __m_latch_18;
	t_sample __m_latch_21;
	t_sample __m_slide_71;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_history_6 = ((int)0);
		m_history_7 = ((int)0);
		m_knob_8 = ((int)0);
		m_knob_9 = ((int)0);
		m_button_10 = ((int)0);
		samples_to_seconds = (1 / samplerate);
		__m_phasor_11.reset(0);
		__m_change_12.reset(0);
		__m_delta_13.reset(0);
		__m_change_14.reset(0);
		__m_change_15.reset(0);
		__m_pluseq_16.reset(0);
		__m_change_17.reset(0);
		__m_latch_18 = 0;
		__m_cycle_19.reset(samplerate, 0);
		__m_change_20.reset(0);
		__m_latch_21 = 0;
		__m_slide_22 = 0;
		__m_latch_25 = 0;
		__m_cycle_26.reset(samplerate, 0);
		__m_change_27.reset(0);
		__m_latch_28 = 0;
		__m_slide_29 = 0;
		__m_latch_32 = 0;
		__m_cycle_33.reset(samplerate, 0);
		__m_change_34.reset(0);
		__m_latch_35 = 0;
		__m_slide_36 = 0;
		__m_latch_39 = 0;
		__m_cycle_40.reset(samplerate, 0);
		__m_change_41.reset(0);
		__m_latch_42 = 0;
		__m_slide_43 = 0;
		__m_latch_46 = 0;
		__m_cycle_47.reset(samplerate, 0);
		__m_change_48.reset(0);
		__m_latch_49 = 0;
		__m_slide_50 = 0;
		__m_latch_53 = 0;
		__m_cycle_54.reset(samplerate, 0);
		__m_change_55.reset(0);
		__m_latch_56 = 0;
		__m_slide_57 = 0;
		__m_latch_60 = 0;
		__m_cycle_61.reset(samplerate, 0);
		__m_change_62.reset(0);
		__m_latch_63 = 0;
		__m_slide_64 = 0;
		__m_latch_67 = 0;
		__m_cycle_68.reset(samplerate, 0);
		__m_change_69.reset(0);
		__m_latch_70 = 0;
		__m_slide_71 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		samples_to_seconds = (1 / samplerate);
		t_sample history_8_next_44 = fixdenorm(((t_sample)0.5));
		int int_70 = int(m_button_10);
		t_sample iup_23 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_24 = (1 / maximum(1, abs(((int)0))));
		t_sample iup_30 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_31 = (1 / maximum(1, abs(((int)0))));
		t_sample iup_37 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_38 = (1 / maximum(1, abs(((int)0))));
		t_sample iup_44 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_45 = (1 / maximum(1, abs(((int)0))));
		t_sample iup_51 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_52 = (1 / maximum(1, abs(((int)0))));
		t_sample iup_58 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_59 = (1 / maximum(1, abs(((int)0))));
		t_sample iup_65 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_66 = (1 / maximum(1, abs(((int)0))));
		t_sample iup_72 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_73 = (1 / maximum(1, abs(((int)0))));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample phasor_189 = __m_phasor_11(((t_sample)1.2333333333333), samples_to_seconds);
			t_sample mul_13 = (phasor_189 * ((int)2));
			t_sample sub_29 = (phasor_189 - m_history_7);
			t_sample add_30 = (phasor_189 + m_history_7);
			t_sample div_28 = safediv(sub_29, add_30);
			t_sample abs_27 = fabs(div_28);
			int gt_25 = (abs_27 > ((t_sample)0.5));
			int change_24 = __m_change_12(gt_25);
			int gt_23 = (change_24 > ((int)0));
			int gen_32 = gt_23;
			t_sample history_26_next_31 = fixdenorm(phasor_189);
			t_sample delta_38 = __m_delta_13(phasor_189);
			t_sample wrap_39 = wrap(delta_38, (-0.5), ((t_sample)0.5));
			t_sample gen_40 = wrap_39;
			t_sample mul_35 = (gen_40 * ((int)2));
			t_sample add_33 = (mul_35 + m_history_4);
			t_sample sub_11 = (add_33 - mul_13);
			t_sample round_22 = (trunc((sub_11 * ((t_sample)0.5))) * ((int)2));
			t_sample add_12 = (round_22 + mul_13);
			t_sample sub_42 = (m_history_5 - ((t_sample)0.5));
			t_sample add_43 = (m_history_5 + ((t_sample)0.5));
			t_sample div_41 = safediv(sub_42, add_43);
			t_sample abs_6 = fabs(div_41);
			int gt_7 = (abs_6 > ((t_sample)0.015625));
			int and_10 = (gt_7 && ((int)1));
			t_sample switch_14 = (and_10 ? and_10 : m_history_6);
			t_sample switch_17 = (gen_32 ? switch_14 : ((int)0));
			t_sample gen_20 = switch_17;
			t_sample switch_16 = (switch_17 ? ((int)0) : switch_14);
			t_sample history_18_next_19 = fixdenorm(switch_16);
			int or_9 = (gen_20 || ((int)0));
			t_sample switch_37 = (or_9 ? add_12 : add_33);
			t_sample wrap_34 = wrap(switch_37, ((int)0), ((int)1));
			t_sample gen_46 = wrap_34;
			t_sample history_36_next_45 = fixdenorm(wrap_34);
			t_sample wrap_48 = wrap(gen_46, ((int)0), ((int)1));
			t_sample sub_196 = (wrap_48 - m_history_3);
			t_sample add_197 = (wrap_48 + m_history_3);
			t_sample div_195 = safediv(sub_196, add_197);
			t_sample abs_194 = fabs(div_195);
			int gt_190 = (abs_194 > ((t_sample)0.5));
			int change_198 = __m_change_14(gt_190);
			int gt_193 = (change_198 > ((int)0));
			int gen_47 = gt_193;
			t_sample history_26_next_192 = fixdenorm(wrap_48);
			t_sample sub_208 = (gen_47 - m_history_2);
			t_sample add_205 = (gen_47 + m_history_2);
			t_sample div_207 = safediv(sub_208, add_205);
			t_sample abs_202 = fabs(div_207);
			int gt_203 = (abs_202 > ((t_sample)0.5));
			int change_201 = __m_change_15(gt_203);
			int gt_204 = (change_201 > ((int)0));
			int gen_52 = gt_204;
			t_sample history_26_next_206 = fixdenorm(gen_47);
			t_sample plusequals_51 = __m_pluseq_16.post(safediv(8, samplerate), gen_52, 0);
			t_sample clamp_50 = ((plusequals_51 <= ((int)0)) ? ((int)0) : ((plusequals_51 >= ((int)1)) ? ((int)1) : plusequals_51));
			t_sample sub_877 = (clamp_50 - ((int)0));
			t_sample scale_874 = ((safepow((sub_877 * ((t_sample)1)), (1 * ((t_sample)0.25))) * ((int)-1)) + ((int)1));
			t_sample scale_53 = scale_874;
			t_sample sub_881 = (scale_53 - ((int)1));
			t_sample scale_878 = ((safepow((sub_881 * ((t_sample)-1)), ((int)1)) * ((int)-100)) + ((int)150));
			t_sample scale_56 = scale_878;
			t_sample sin_57 = sin(scale_56);
			t_sample mul_58 = (scale_53 * sin_57);
			t_sample mix_882 = (mul_58 + (((t_sample)0.9) * (m_history_1 - mul_58)));
			t_sample mix_55 = mix_882;
			t_sample gen_60 = mix_55;
			t_sample history_54_next_59 = fixdenorm(mix_55);
			t_sample mul_49 = (m_knob_9 * gen_60);
			t_sample mul_3 = (mul_49 * ((t_sample)0.25));
			t_sample mul_188 = (phasor_189 * ((int)8));
			t_sample floor_187 = floor(mul_188);
			int eq_186 = (floor_187 == ((int)0));
			int eq_116 = (floor_187 == ((int)4));
			int eq_136 = (floor_187 == ((int)6));
			int eq_166 = (floor_187 == ((int)2));
			int eq_146 = (floor_187 == ((int)5));
			int eq_126 = (floor_187 == ((int)7));
			int eq_156 = (floor_187 == ((int)3));
			int eq_176 = (floor_187 == ((int)1));
			t_sample noise_104 = noise();
			t_sample noise_131 = noise();
			t_sample noise_161 = noise();
			t_sample noise_181 = noise();
			t_sample noise_141 = noise();
			t_sample noise_121 = noise();
			t_sample noise_151 = noise();
			t_sample noise_171 = noise();
			int change_71 = __m_change_17(int_70);
			int eqp_72 = ((int_70 == change_71) ? int_70 : 0);
			__m_latch_18 = ((eqp_72 != 0) ? noise_104 : __m_latch_18);
			t_sample latch_101 = __m_latch_18;
			t_sample sub_886 = (latch_101 - (-1));
			t_sample scale_883 = ((safepow((sub_886 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_102 = mtof(scale_883, ((int)440));
			__m_cycle_19.freq(mtof_102);
			t_sample cycle_114 = __m_cycle_19(__sinedata);
			t_sample cycleindex_115 = __m_cycle_19.phase();
			int gt_110 = (cycle_114 > ((int)0));
			int change_109 = __m_change_20(gt_110);
			__m_latch_21 = ((change_109 != 0) ? eq_116 : __m_latch_21);
			int latch_108 = __m_latch_21;
			__m_slide_22 = fixdenorm((__m_slide_22 + (((latch_108 > __m_slide_22) ? iup_23 : idown_24) * (latch_108 - __m_slide_22))));
			t_sample slide_107 = __m_slide_22;
			t_sample mul_111 = (cycle_114 * slide_107);
			t_sample mul_69 = (mul_111 * ((t_sample)0.25));
			__m_latch_25 = ((eqp_72 != 0) ? noise_131 : __m_latch_25);
			t_sample latch_128 = __m_latch_25;
			t_sample sub_890 = (latch_128 - (-1));
			t_sample scale_887 = ((safepow((sub_890 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_129 = mtof(scale_887, ((int)440));
			__m_cycle_26.freq(mtof_129);
			t_sample cycle_134 = __m_cycle_26(__sinedata);
			t_sample cycleindex_135 = __m_cycle_26.phase();
			int gt_215 = (cycle_134 > ((int)0));
			int change_213 = __m_change_27(gt_215);
			__m_latch_28 = ((change_213 != 0) ? eq_136 : __m_latch_28);
			int latch_214 = __m_latch_28;
			__m_slide_29 = fixdenorm((__m_slide_29 + (((latch_214 > __m_slide_29) ? iup_30 : idown_31) * (latch_214 - __m_slide_29))));
			t_sample slide_210 = __m_slide_29;
			t_sample mul_212 = (cycle_134 * slide_210);
			t_sample mul_67 = (mul_212 * ((t_sample)0.25));
			__m_latch_32 = ((eqp_72 != 0) ? noise_161 : __m_latch_32);
			t_sample latch_158 = __m_latch_32;
			t_sample sub_894 = (latch_158 - (-1));
			t_sample scale_891 = ((safepow((sub_894 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_159 = mtof(scale_891, ((int)440));
			__m_cycle_33.freq(mtof_159);
			t_sample cycle_164 = __m_cycle_33(__sinedata);
			t_sample cycleindex_165 = __m_cycle_33.phase();
			int gt_223 = (cycle_164 > ((int)0));
			int change_220 = __m_change_34(gt_223);
			__m_latch_35 = ((change_220 != 0) ? eq_166 : __m_latch_35);
			int latch_221 = __m_latch_35;
			__m_slide_36 = fixdenorm((__m_slide_36 + (((latch_221 > __m_slide_36) ? iup_37 : idown_38) * (latch_221 - __m_slide_36))));
			t_sample slide_217 = __m_slide_36;
			t_sample mul_219 = (cycle_164 * slide_217);
			t_sample mul_63 = (mul_219 * ((t_sample)0.25));
			__m_latch_39 = ((eqp_72 != 0) ? noise_181 : __m_latch_39);
			t_sample latch_178 = __m_latch_39;
			t_sample sub_898 = (latch_178 - (-1));
			t_sample scale_895 = ((safepow((sub_898 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_179 = mtof(scale_895, ((int)440));
			__m_cycle_40.freq(mtof_179);
			t_sample cycle_184 = __m_cycle_40(__sinedata);
			t_sample cycleindex_185 = __m_cycle_40.phase();
			int gt_230 = (cycle_184 > ((int)0));
			int change_227 = __m_change_41(gt_230);
			__m_latch_42 = ((change_227 != 0) ? eq_186 : __m_latch_42);
			int latch_228 = __m_latch_42;
			__m_slide_43 = fixdenorm((__m_slide_43 + (((latch_228 > __m_slide_43) ? iup_44 : idown_45) * (latch_228 - __m_slide_43))));
			t_sample slide_224 = __m_slide_43;
			t_sample mul_226 = (cycle_184 * slide_224);
			t_sample mul_65 = (mul_226 * ((t_sample)0.25));
			t_sample l_75 = (((mul_65 + mul_63) + mul_67) + mul_69);
			t_sample sub_2 = (l_75 - mul_3);
			t_sample out1 = (mul_49 + sub_2);
			__m_latch_46 = ((eqp_72 != 0) ? noise_141 : __m_latch_46);
			t_sample latch_138 = __m_latch_46;
			t_sample sub_902 = (latch_138 - (-1));
			t_sample scale_899 = ((safepow((sub_902 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_139 = mtof(scale_899, ((int)440));
			__m_cycle_47.freq(mtof_139);
			t_sample cycle_144 = __m_cycle_47(__sinedata);
			t_sample cycleindex_145 = __m_cycle_47.phase();
			int gt_237 = (cycle_144 > ((int)0));
			int change_234 = __m_change_48(gt_237);
			__m_latch_49 = ((change_234 != 0) ? eq_146 : __m_latch_49);
			int latch_235 = __m_latch_49;
			__m_slide_50 = fixdenorm((__m_slide_50 + (((latch_235 > __m_slide_50) ? iup_51 : idown_52) * (latch_235 - __m_slide_50))));
			t_sample slide_231 = __m_slide_50;
			t_sample mul_233 = (cycle_144 * slide_231);
			t_sample mul_68 = (mul_233 * ((t_sample)0.25));
			__m_latch_53 = ((eqp_72 != 0) ? noise_121 : __m_latch_53);
			t_sample latch_118 = __m_latch_53;
			t_sample sub_906 = (latch_118 - (-1));
			t_sample scale_903 = ((safepow((sub_906 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_119 = mtof(scale_903, ((int)440));
			__m_cycle_54.freq(mtof_119);
			t_sample cycle_124 = __m_cycle_54(__sinedata);
			t_sample cycleindex_125 = __m_cycle_54.phase();
			int gt_244 = (cycle_124 > ((int)0));
			int change_241 = __m_change_55(gt_244);
			__m_latch_56 = ((change_241 != 0) ? eq_126 : __m_latch_56);
			int latch_242 = __m_latch_56;
			__m_slide_57 = fixdenorm((__m_slide_57 + (((latch_242 > __m_slide_57) ? iup_58 : idown_59) * (latch_242 - __m_slide_57))));
			t_sample slide_238 = __m_slide_57;
			t_sample mul_240 = (cycle_124 * slide_238);
			t_sample mul_66 = (mul_240 * ((t_sample)0.25));
			__m_latch_60 = ((eqp_72 != 0) ? noise_151 : __m_latch_60);
			t_sample latch_148 = __m_latch_60;
			t_sample sub_910 = (latch_148 - (-1));
			t_sample scale_907 = ((safepow((sub_910 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_149 = mtof(scale_907, ((int)440));
			__m_cycle_61.freq(mtof_149);
			t_sample cycle_154 = __m_cycle_61(__sinedata);
			t_sample cycleindex_155 = __m_cycle_61.phase();
			int gt_251 = (cycle_154 > ((int)0));
			int change_248 = __m_change_62(gt_251);
			__m_latch_63 = ((change_248 != 0) ? eq_156 : __m_latch_63);
			int latch_249 = __m_latch_63;
			__m_slide_64 = fixdenorm((__m_slide_64 + (((latch_249 > __m_slide_64) ? iup_65 : idown_66) * (latch_249 - __m_slide_64))));
			t_sample slide_245 = __m_slide_64;
			t_sample mul_247 = (cycle_154 * slide_245);
			t_sample mul_62 = (mul_247 * ((t_sample)0.25));
			__m_latch_67 = ((eqp_72 != 0) ? noise_171 : __m_latch_67);
			t_sample latch_168 = __m_latch_67;
			t_sample sub_914 = (latch_168 - (-1));
			t_sample scale_911 = ((safepow((sub_914 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_169 = mtof(scale_911, ((int)440));
			__m_cycle_68.freq(mtof_169);
			t_sample cycle_174 = __m_cycle_68(__sinedata);
			t_sample cycleindex_175 = __m_cycle_68.phase();
			int gt_258 = (cycle_174 > ((int)0));
			int change_255 = __m_change_69(gt_258);
			__m_latch_70 = ((change_255 != 0) ? eq_176 : __m_latch_70);
			int latch_256 = __m_latch_70;
			__m_slide_71 = fixdenorm((__m_slide_71 + (((latch_256 > __m_slide_71) ? iup_72 : idown_73) * (latch_256 - __m_slide_71))));
			t_sample slide_252 = __m_slide_71;
			t_sample mul_254 = (cycle_174 * slide_252);
			t_sample mul_64 = (mul_254 * ((t_sample)0.25));
			t_sample r_74 = (((mul_64 + mul_62) + mul_66) + mul_68);
			t_sample sub_4 = (r_74 - mul_3);
			t_sample out2 = (mul_49 + sub_4);
			m_history_7 = history_26_next_31;
			m_history_4 = history_36_next_45;
			m_history_5 = history_8_next_44;
			m_history_6 = history_18_next_19;
			m_history_3 = history_26_next_192;
			m_history_2 = history_26_next_206;
			m_history_1 = history_54_next_59;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_knob1(t_param _value) {
		m_knob_8 = (_value < 40 ? 40 : (_value > 200 ? 200 : _value));
	};
	inline void set_knob2(t_param _value) {
		m_knob_9 = (_value < 0 ? 0 : (_value > 0.5 ? 0.5 : _value));
	};
	inline void set_button(t_param _value) {
		m_button_10 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 3; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "out2" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_button(value); break;
		case 1: self->set_knob1(value); break;
		case 2: self->set_knob2(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_button_10; break;
		case 1: *value = self->m_knob_8; break;
		case 2: *value = self->m_knob_9; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(3 * sizeof(ParamInfo));
	self->__commonstate.numparams = 3;
	// initialize parameter 0 ("m_button_10")
	pi = self->__commonstate.params + 0;
	pi->name = "button";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_button_10;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob_8")
	pi = self->__commonstate.params + 1;
	pi->name = "knob1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_8;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 40;
	pi->outputmax = 200;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob_9")
	pi = self->__commonstate.params + 2;
	pi->name = "knob2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_9;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.5;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // daisy_2dtechno_2dmachine::
