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
	Change __m_change_13;
	Change __m_change_16;
	Change __m_change_18;
	Change __m_change_19;
	Change __m_change_24;
	Data m_notes_12;
	Delta __m_delta_17;
	Phasor __m_phasor_15;
	PlusEquals __m_pluseq_14;
	PlusEquals __m_pluseq_20;
	SineCycle __m_cycle_23;
	SineData __sinedata;
	int __exception;
	int vectorsize;
	t_sample m_history_3;
	t_sample m_button_11;
	t_sample m_history_2;
	t_sample m_history_1;
	t_sample samplerate;
	t_sample m_history_4;
	t_sample m_knob_10;
	t_sample m_history_5;
	t_sample m_history_7;
	t_sample __m_latch_25;
	t_sample m_history_6;
	t_sample m_knob_9;
	t_sample samples_to_seconds;
	t_sample m_history_8;
	t_sample __m_slide_26;
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
		m_history_8 = ((int)0);
		m_knob_9 = ((int)0);
		m_knob_10 = ((int)0);
		m_button_11 = ((int)0);
		m_notes_12.reset("notes", ((int)512), ((int)1));
		__m_change_13.reset(0);
		__m_pluseq_14.reset(0);
		samples_to_seconds = (1 / samplerate);
		__m_phasor_15.reset(0);
		__m_change_16.reset(0);
		__m_delta_17.reset(0);
		__m_change_18.reset(0);
		__m_change_19.reset(0);
		__m_pluseq_20.reset(0);
		__m_cycle_23.reset(samplerate, 0);
		__m_change_24.reset(0);
		__m_latch_25 = 0;
		__m_slide_26 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		const t_sample * __in3 = __ins[2];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__in3 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		int notes_dim = m_notes_12.dim;
		int notes_channels = m_notes_12.channels;
		int int_182 = int(m_button_11);
		samples_to_seconds = (1 / samplerate);
		t_sample history_120_next_156 = fixdenorm(((t_sample)0.5));
		t_sample iup_27 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_28 = (1 / maximum(1, abs(((int)0))));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			const t_sample in3 = (*(__in3++));
			m_notes_12.write(((int)0), 0, 0);
			int lt_3366 = (m_history_1 < ((int)8));
			int change_183 = __m_change_13(int_182);
			int eqp_184 = ((int_182 == change_183) ? int_182 : 0);
			int gen_185 = eqp_184;
			t_sample plusequals_2982 = __m_pluseq_14.post(lt_3366, (in3 + gen_185), 0);
			t_sample phasor_301 = __m_phasor_15(((t_sample)1.2333333333333), samples_to_seconds);
			t_sample mul_125 = (phasor_301 * ((int)2));
			t_sample sub_141 = (phasor_301 - m_history_8);
			t_sample add_142 = (phasor_301 + m_history_8);
			t_sample div_140 = safediv(sub_141, add_142);
			t_sample abs_139 = fabs(div_140);
			int gt_137 = (abs_139 > ((t_sample)0.5));
			int change_136 = __m_change_16(gt_137);
			int gt_135 = (change_136 > ((int)0));
			int gen_144 = gt_135;
			t_sample history_138_next_143 = fixdenorm(phasor_301);
			t_sample delta_150 = __m_delta_17(phasor_301);
			t_sample wrap_151 = wrap(delta_150, (-0.5), ((t_sample)0.5));
			t_sample gen_152 = wrap_151;
			t_sample mul_147 = (gen_152 * ((int)2));
			t_sample add_145 = (mul_147 + m_history_5);
			t_sample sub_123 = (add_145 - mul_125);
			t_sample round_134 = (trunc((sub_123 * ((t_sample)0.5))) * ((int)2));
			t_sample add_124 = (round_134 + mul_125);
			t_sample sub_154 = (m_history_6 - ((t_sample)0.5));
			t_sample add_155 = (m_history_6 + ((t_sample)0.5));
			t_sample div_153 = safediv(sub_154, add_155);
			t_sample abs_118 = fabs(div_153);
			int gt_119 = (abs_118 > ((t_sample)0.015625));
			int and_122 = (gt_119 && ((int)1));
			t_sample switch_126 = (and_122 ? and_122 : m_history_7);
			t_sample switch_129 = (gen_144 ? switch_126 : ((int)0));
			t_sample gen_132 = switch_129;
			t_sample switch_128 = (switch_129 ? ((int)0) : switch_126);
			t_sample history_130_next_131 = fixdenorm(switch_128);
			int or_121 = (gen_132 || ((int)0));
			t_sample switch_149 = (or_121 ? add_124 : add_145);
			t_sample wrap_146 = wrap(switch_149, ((int)0), ((int)1));
			t_sample gen_158 = wrap_146;
			t_sample history_148_next_157 = fixdenorm(wrap_146);
			t_sample wrap_160 = wrap(gen_158, ((int)0), ((int)1));
			t_sample sub_3644 = (wrap_160 - m_history_4);
			t_sample add_3638 = (wrap_160 + m_history_4);
			t_sample div_3640 = safediv(sub_3644, add_3638);
			t_sample abs_3637 = fabs(div_3640);
			int gt_3641 = (abs_3637 > ((t_sample)0.5));
			int change_3642 = __m_change_18(gt_3641);
			int gt_3639 = (change_3642 > ((int)0));
			int gen_159 = gt_3639;
			t_sample history_138_next_3643 = fixdenorm(wrap_160);
			t_sample sub_3654 = (gen_159 - m_history_3);
			t_sample add_3652 = (gen_159 + m_history_3);
			t_sample div_3655 = safediv(sub_3654, add_3652);
			t_sample abs_3650 = fabs(div_3655);
			int gt_3651 = (abs_3650 > ((t_sample)0.5));
			int change_3649 = __m_change_19(gt_3651);
			int gt_3648 = (change_3649 > ((int)0));
			int gen_164 = gt_3648;
			t_sample history_138_next_3647 = fixdenorm(gen_159);
			t_sample plusequals_163 = __m_pluseq_20.post(safediv(8, samplerate), gen_164, 0);
			t_sample clamp_162 = ((plusequals_163 <= ((int)0)) ? ((int)0) : ((plusequals_163 >= ((int)1)) ? ((int)1) : plusequals_163));
			t_sample sub_3670 = (clamp_162 - ((int)0));
			t_sample scale_3667 = ((safepow((sub_3670 * ((t_sample)1)), (1 * ((t_sample)0.25))) * ((int)-1)) + ((int)1));
			t_sample scale_165 = scale_3667;
			t_sample sub_3674 = (scale_165 - ((int)1));
			t_sample scale_3671 = ((safepow((sub_3674 * ((t_sample)-1)), ((int)1)) * ((int)-100)) + ((int)150));
			t_sample scale_168 = scale_3671;
			t_sample sin_169 = sin(scale_168);
			t_sample mul_170 = (scale_165 * sin_169);
			t_sample mix_3675 = (mul_170 + (((t_sample)0.9) * (m_history_2 - mul_170)));
			t_sample mix_167 = mix_3675;
			t_sample gen_172 = mix_167;
			t_sample history_166_next_171 = fixdenorm(mix_167);
			t_sample mul_161 = (m_knob_9 * gen_172);
			t_sample mul_115 = (mul_161 * ((t_sample)0.25));
			t_sample sub_116 = (((int)0) - mul_115);
			t_sample out2 = (mul_161 + sub_116);
			t_sample mul_300 = (phasor_301 * ((int)8));
			t_sample floor_299 = floor(mul_300);
			int eq_298 = (floor_299 == ((int)0));
			int index_trunc_21 = fixnan(floor(floor_299));
			bool index_ignore_22 = ((index_trunc_21 >= notes_dim) || (index_trunc_21 < 0));
			// samples notes channel 1;
			t_sample sample_notes_1486 = (index_ignore_22 ? 0 : m_notes_12.read(index_trunc_21, 0));
			t_sample index_notes_1487 = floor_299;
			__m_cycle_23.freq(sample_notes_1486);
			t_sample cycle_296 = __m_cycle_23(__sinedata);
			t_sample cycleindex_297 = __m_cycle_23.phase();
			int gt_222 = (cycle_296 > ((int)0));
			int change_221 = __m_change_24(gt_222);
			__m_latch_25 = ((change_221 != 0) ? eq_298 : __m_latch_25);
			int latch_220 = __m_latch_25;
			__m_slide_26 = fixdenorm((__m_slide_26 + (((latch_220 > __m_slide_26) ? iup_27 : idown_28) * (latch_220 - __m_slide_26))));
			t_sample slide_219 = __m_slide_26;
			t_sample mul_223 = (cycle_296 * slide_219);
			t_sample mul_177 = (mul_223 * ((t_sample)0.25));
			t_sample sub_114 = (mul_177 - mul_115);
			t_sample out1 = (mul_161 + sub_114);
			t_sample history_3443_next_3657 = fixdenorm(plusequals_2982);
			m_history_8 = history_138_next_143;
			m_history_5 = history_148_next_157;
			m_history_6 = history_120_next_156;
			m_history_7 = history_130_next_131;
			m_history_4 = history_138_next_3643;
			m_history_3 = history_138_next_3647;
			m_history_2 = history_166_next_171;
			m_history_1 = history_3443_next_3657;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_knob2(t_param _value) {
		m_knob_9 = (_value < 0 ? 0 : (_value > 0.5 ? 0.5 : _value));
	};
	inline void set_knob1(t_param _value) {
		m_knob_10 = (_value < 40 ? 40 : (_value > 200 ? 200 : _value));
	};
	inline void set_button(t_param _value) {
		m_button_11 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_notes(void * _value) {
		m_notes_12.setbuffer(_value);
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 3;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 4; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2", "in3" };
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
		case 3: self->set_notes(ref); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_button_11; break;
		case 1: *value = self->m_knob_10; break;
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(4 * sizeof(ParamInfo));
	self->__commonstate.numparams = 4;
	// initialize parameter 0 ("m_button_11")
	pi = self->__commonstate.params + 0;
	pi->name = "button";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_button_11;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob_10")
	pi = self->__commonstate.params + 1;
	pi->name = "knob1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_10;
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
	// initialize parameter 3 ("m_notes_12")
	pi = self->__commonstate.params + 3;
	pi->name = "notes";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
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
