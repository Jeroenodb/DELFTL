/**
 * Author: Jeroen Op de Beek
 * Date: 2024-08-27
 * License: CC0
 * Source: me
 * Description: Segment tree which can do x[i] := x[i]*a + b on a range, and range sum
 * Can be changed to other things.
 * Can be used as is for range set, range add, and range sum by using a=0,b=v, and a=1,b=v updates.
 * Time: O(\log N) for all operations, O(n) build time.
 * Usage: segtree seg(n); for(int i=0;i<n;++i) seg[i].v = {a[i],1}; seg.build(); seg.update(l,r,{1,1}), seg.get(l,r);
 * Status: Accepted on CSES range add, range set, range sum.
 */
#pragma once

struct segtree {
    int n,ptwo=1;
    struct U { // updates: 
        ll a=1,b=0; // identity update
        void operator+=(U u) { a*=u.a, b = b*u.a + u.b; } // stack update on another, U u is the newer update.
    };
    struct V {
        ll sum=0;
        int len=0;
        V upd(U u) const { return {sum*u.a + u.b*len, len}; } // effect of update on V
        V operator+(V o) const { return {sum+o.sum, len+o.len}; } // merge two values
    };
    struct node { 
        V v; U u;
        V getv() { return v.upd(u); }
    };
    vector<node> seg;
    segtree(){}
    segtree(int nn) : n(nn) {
        while(ptwo<n) ptwo*=2;
        seg.assign(ptwo*2,{});
    }
    void push(int i) {
        U u = seg[i].u;
        seg[i].v = seg[i].v.upd(u);
        seg[i*2].u+=u, seg[i*2+1].u+=u;
        seg[i].u = {};
    }
    void pull(int i) { seg[i].v = seg[i*2].getv() + seg[i*2+1].getv(); }
    void upd(int i, int l, int r, int ql ,int qr, U u) {
        if(qr<=l or r<=ql) return;
        if(ql<=l and r<=qr) return void(seg[i].u+=u);
        int mid = (l+r)/2;
        push(i);
        upd(i*2,l,mid,ql,qr,u);
        upd(i*2+1,mid,r,ql,qr,u);
        pull(i);
    }
    V gt(int i, int l, int r, int ql, int qr) {
        if(qr<=l or r<=ql) return {};
        if(ql<=l and r<=qr) return seg[i].getv();
        int mid = (l+r)/2;
        push(i);
        return gt(i*2,l,mid,ql,qr)+gt(i*2+1,mid,r,ql,qr);
    }
    void update(int l, int r, U u) { upd(1,0,ptwo,l,r,u); } // [l,r)
    V get(int l, int r) {return gt(1,0,ptwo,l,r); } // [l,r)
    void build() { for(int i=ptwo-1;i>=1;--i) pull(i); }
    node& operator[](int i) {return seg[i+ptwo];}
};