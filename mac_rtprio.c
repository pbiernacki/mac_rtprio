#include <sys/param.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/priv.h>
#include <sys/sysctl.h>
#include <sys/systm.h>
#include <sys/ucred.h>

#include <security/mac/mac_policy.h>

SYSCTL_DECL(_security_mac);

static SYSCTL_NODE(_security_mac, OID_AUTO, rtprio, CTLFLAG_RW, 0,
        "mac_rtprio policy controls");

static int rtprio_enabled = 0;
SYSCTL_INT(_security_mac_rtprio, OID_AUTO, enabled, CTLFLAG_RW,
        &rtprio_enabled, 0, "Enforce mac_rtprio policy");

static int rtprio_gid = -1;
SYSCTL_INT(_security_mac_rtprio, OID_AUTO, gid, CTLFLAG_RW,
        &rtprio_gid, 0, "Group ID that can change rtprio");

static int
rtprio_priv_grant(struct ucred *cred, int priv)
{
    if (!rtprio_enabled || priv != PRIV_SCHED_RTPRIO) {
        return (EPERM);
    }

    if (rtprio_gid >= 0) {
        if (groupmember(rtprio_gid, cred)) {
            return (0);
        }
    }

    return (EPERM);
}

static struct mac_policy_ops rtprio_ops =
{
    .mpo_priv_grant = rtprio_priv_grant,
};

MAC_POLICY_SET(&rtprio_ops, mac_rtprio, "MAC/rtprio",
        MPC_LOADTIME_FLAG_UNLOADOK, NULL);

