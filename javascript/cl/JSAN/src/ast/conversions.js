/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2018 Department of Software Engineering - University of Szeged
 *
 *  Licensed under Version 1.2 of the EUPL (the "Licence");
 *
 *  You may not use this work except in compliance with the Licence.
 *
 *  You may obtain a copy of the Licence in the LICENSE file or at:
 *
 *  https://joinup.ec.europa.eu/software/page/eupl
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the Licence for the specific language governing permissions and
 *  limitations under the Licence.
 */

const propertyKinds = {
    'init': 'pkInit',
    'get': 'pkGet',
    'set': 'pkSet'
};

const declarationKinds = {
    'var': 'dkVar',
    'let': 'dkLet',
    'const': 'dkConst'
};

const methodDefinitionKinds = {
    'constructor': 'mdkConstructor',
    'method': 'mdkMethod',
    'set': 'mdkSet',
    'get': 'mdkGet'
};

const sourceTypes = {
    'script': 'pstScript',
    'module': 'pstModule'
};

const unaryOperators = {
    '-': "unoMinus",
    '+': "unoPlus",
    '!': "unoNot",
    'typeof': "unoTypeOf",
    'void': "unoVoid",
    'delete': "unoDelete",
    '~': "unoBitwiseNot",
};

const additionalOperators = {
    '==': 'bioEqualTo',
    '!=': 'bioNotEqual',
    '===': 'bioEqualValueAndType',
    '!==': 'bioNotEqualValueAndType',
    '<': 'bioLessThan',
    '>': 'bioGreaterThan',
    '>=': 'bioGreaterThanEqual',
    '<=': 'bioLessThanEqual',
    '<<': 'bioLeftShift',
    '>>': 'bioRightShift',
    '>>>': 'bioFillNullRightShift',
    '+': 'bioAddition',
    '-': 'bioSubtraction',
    '*': 'bioMultiplication',
    '/': 'bioDivision',
    '%': 'bioModulus',
    '|': 'bioOr',
    '^': 'bioXor',
    '&': 'bioAnd',
    'instanceof': 'bioInstanceOf',
    'in': 'bioIn',
    '**': 'bioExponentiation',
    '++': 'upoIncrement',
    '--': 'upoDecrement',
    '&&': 'looAnd',
    '||': 'looOr',
    '=': 'asoAssign',
    '+=': 'asoAdd',
    '-=': 'asoSubtract',
    '*=': 'asoMultiplication',
    '/=': 'asoDivision',
    '%=': 'asoModulus',
    '<<=': 'asoLeftShift',
    '>>=': 'asoRightShift',
    '>>>=': 'asoFillNullRightShift',
    '|=': 'asoBitwiseOr',
    '^=': 'asoBitwiseXor',
    '&=': 'asoBitwiseAnd',
    '**=': 'asoExponentiation'
};


//--------------------------
//-----Module Exports-------
//--------------------------
module.exports.convertPropertyKind = function (kind) {
    return propertyKinds[kind] === undefined ? 'unrecognized' : propertyKinds[kind];
};

module.exports.convertDeclarationKind = function (kind) {
    return declarationKinds[kind] === undefined ? 'unrecognized' : declarationKinds[kind];
};

module.exports.convertMethodDefinitionKind = function (kind) {
    return methodDefinitionKinds[kind] === undefined ? 'unrecognized' : methodDefinitionKinds[kind];
};

module.exports.convertSourceType = function (sourcetype) {
    return sourceTypes[sourcetype] === undefined ? 'unrecognized' : sourceTypes[sourcetype];
};

module.exports.convertUnaryOperatorToString = function (operator) {
    return unaryOperators[operator] === undefined ? 'unrecognized' : unaryOperators[operator];
};

module.exports.convertOperatorToString = function (operator) {
    return additionalOperators[operator] === undefined ? 'unrecognized' : additionalOperators[operator];
};
